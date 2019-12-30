#include "QZSyncWorker.h"
#include "Poco/Util/Application.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/Statement.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/FileStream.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPResponse.h"
#include "OESSealProvider.h"
#include "XSSealProvider.h"
#include "KGSealProvider.h"
#include "Utility.h"
#include <cassert>

using namespace Reach;
using namespace Reach::ActiveX;
using namespace Poco;
using namespace Poco::Data;
using namespace Poco::Data::SQLite;
using namespace Poco::Data::Keywords;
using namespace Poco::JSON;
using namespace Poco::Net;
using Poco::Dynamic::Var;
using Poco::Util::Application;

QZSyncWorker::QZSyncWorker()
	:Task("QZSyncWorker")
{
	Poco::Data::SQLite::Connector::registerConnector();
	FileInputStream in(Utility::config("QZSyncWorker.json"));
	object = extract<Object::Ptr>(in);
	assert(object);
	if (!object)
		throw Poco::UnhandledException("config lost", "QZSyncWorker.json");
}

void QZSyncWorker::runTask()
{
	Application& app = Application::instance();

	while (!sleep(5000))
	{
		app.logger().trace("busy doing QZSyncTask... " + DateTimeFormatter::format(app.uptime()));
		if (isCancelled()) break;
		try
		{
			if (IsUSBKeyPresent()) {
				composite();
				updateStatus();
				transfer();
			}
		}
		catch (Poco::Exception& e)
		{
			std::string message(format("QZSyncWorker runTask Exception: %d, %s", e.code(), e.message()));
			log(message);
		}
		
	}
}

bool QZSyncWorker::IsUSBKeyPresent()
{
	return true;
}

void QZSyncWorker::composite()
{
	Application& app = Application::instance();

	typedef std::vector<Poco::AutoPtr<SealProvider>> SPVec;
	typedef std::vector<Poco::AutoPtr<SealProvider>>::iterator SPIter;
	SPVec oess;
	oess.push_back(new OESSealProvider);
	oess.push_back(new XSSealProvider);
	oess.push_back(new KGSealProvider);
	for (SPIter it = oess.begin(); it != oess.end(); it++)
	{
		try
		{
			Poco::AutoPtr<SealProvider> ptr = *it;
			assert(ptr);
			ptr->extract();
			_name = ptr->getProperty("name");
			_code = ptr->getProperty("code");
			_validStart = ptr->getProperty("validStart");
			_validEnd = ptr->getProperty("validEnd");
			_keysn = ptr->getProperty("keysn");
			_seals = ptr->getProperty("seals");
			_md5 = ptr->getProperty("dataMD5");

			std::string message;
			message.append(format("name:%s,code%:%s \n", ptr->getProperty("name"), ptr->getProperty("code")));
			message.append(format("validStart:%s,validEnd%:%s\n", ptr->getProperty("validStart"), ptr->getProperty("validEnd")));
			message.append(format("keysn:%s,dataMD5%:%s\n", ptr->getProperty("keysn"), ptr->getProperty("dataMD5")));
			message.append(format("seal -> \n%s", ptr->getProperty("seals")));
			log(message);
			
			break;
		}
		catch (Poco::Exception& e)
		{
			std::string message(format("QZSyncWorker Composite Exception %[1]d : %[0]s", e.message(), e.code()));
			log(message);
		}
	}
}

void QZSyncWorker::updateStatus()
{
	/// | Title		 |	T	|	F	|	T	|	F	|
	/// | MD5		 |	1	|	1	|	0	|	0	|
	/// | sync		 |	1	|	0	|	1	|	0	|
	///	| transfer   |	No	|	Yes	|	Yes	|	YES	|
	/// | Final		 |		|	Y	|		|		|

	Application& app = Application::instance();
#ifdef _DEBUG
	Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
	Session session("SQLite", "DeQLite.db");
#endif // _DEBUG

	struct Makeup {
		int id;
		std::string keysn;
		std::string md5;
		bool sync;
	};

	Makeup syncRecord;
	Statement select(session);
	select << "SELECT id, keysn, md5value, sync FROM syncSDMakeup WHERE keysn = ?",
		into(syncRecord.id),
		into(syncRecord.keysn),
		into(syncRecord.md5),
		into(syncRecord.sync),
		use(_keysn),
		range(0, 1);

	while (!select.done()) {

		if (!select.execute()) {
			Statement insert(session);
			insert << "INSERT INTO syncSDMakeup (keysn, md5value) VALUES (?, ?);",
				use(_keysn),
				use(_md5),
				sync,
				now;

			log(format("insert SQL Statement :%s, keysn=%s, md5value=%s",insert.toString(), _keysn, _md5));

			break;
		}

		log(format("select SQL Statement :%s ,keysn= %s, md5value=%s, sync = %b", select.toString(), syncRecord.keysn, syncRecord.md5, syncRecord.sync));

		if (syncRecord.md5 != _md5) {

			Statement update(session);
			update << "UPDATE syncSDMakeup set md5value = ?, sync = 0, modify_time = datetime('now','localtime') where keysn= ?;",
				use(_md5),
				use(syncRecord.keysn),
				sync,
				now;

			log(format("update SQL Statement :%s when the md5 is different, keysn=%s, md5value=%s sync = 0", update.toString(), syncRecord.keysn, _md5));
		}
	}
}

void QZSyncWorker::transfer()
{
	Application& app = Application::instance();
	Object check; DynamicStruct ds = *object;
	check.set("appcode",	ds["fmt"]["appcode"].toString());
	check.set("keysn",		_keysn);
	check.set("dataMD5",	_md5);

	log(format("check : %s\n ", Var(check).convert<std::string>()));

	std::string data = Var(check).convert<std::string>();
	URI uri(ds["url"]["check"].toString());
	HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
	HTTPClientSession session(uri.getHost(), uri.getPort());
	request.setContentLength((int)data.length());
	session.sendRequest(request) << data;

	HTTPResponse response;
	std::istream& out = session.receiveResponse(response);
	DynamicStruct res = *extract<Object::Ptr>(out);

	if (res["code"] == "0" || res["code"] == "7") { /// sync
		ds["fmt"]["keysn"] = _keysn;
		ds["fmt"]["dataMD5"] = _md5;
		ds["fmt"]["username"] = _name;
		ds["fmt"]["usercode"] = _code;
		ds["fmt"]["validStart"] = _validStart;
		ds["fmt"]["validEnd"] = _validEnd;
		ds["fmt"]["seals"] = _seals;

		std::string data = ds["fmt"].toString();
		URI uri(ds["url"]["sync"].toString());
		HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
		HTTPClientSession session(uri.getHost(), uri.getPort());
		request.setContentLength((int)data.length());
		session.sendRequest(request) << data;

		HTTPResponse response;
		std::istream& out = session.receiveResponse(response);
		DynamicStruct res = *extract<Object::Ptr>(out);
		log(format("code:%s message:%s\n", res["code"].toString(), res["message"].toString()));
	}
	setSync(_keysn);
}

void QZSyncWorker::setSync(std::string& keysn, bool flag)
{
	Application& app = Application::instance();
#ifdef _DEBUG
	Poco::Data::Session session("SQLite", "C:\\Windows\\SysWOW64\\DeQLite.db");
#else
	Poco::Data::Session session("SQLite", "DeQLite.db");
#endif // _DEBUG

	Statement select(session);
	select << "UPDATE syncSDMakeup set sync = ? WHERE keysn = ?;",
		use(flag),use(keysn), range(0, 1), sync, now;

	log(format("setSync SQL Statement :%s keysn=%s, sync=%b", select.toString(), keysn, flag));
}

void QZSyncWorker::log(const std::string& message)
{
	Application& app = Application::instance();

	std::ostringstream ostr;
	std::string stringToken(100, '#');

	ostr << std::endl
		<< stringToken
		<< std::endl
		<< message
		<< std::endl
		<< stringToken
		<< std::endl << std::endl;

	poco_information(app.logger(), ostr.str());
}