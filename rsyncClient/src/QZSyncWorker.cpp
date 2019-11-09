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
#include <cassert>

using namespace Reach;

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
	FileInputStream in("QZSyncWorker.json");
	object = extract<Object::Ptr>(in);
	assert(object);
}

void QZSyncWorker::runTask()
{
	Application& app = Application::instance();

	while (!sleep(2000))
	{
		app.logger().trace("busy doing QZSyncTask... " + DateTimeFormatter::format(app.uptime()));

		if (IsUSBKeyPresent()) {
			composite();
			updateStatus();
			transfer();
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

	OESSealProvider oes;
	oes.extract();
	_name = oes.getProperty("name");
	_code = oes.getProperty("code");
	_validStart = oes.getProperty("validStart");
	_validEnd = oes.getProperty("validEnd");
	_keysn = oes.getProperty("keysn");
	_seals = oes.getProperty("seals");
	_md5 = oes.getProperty("dataMD5");
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

			break;
		}
		poco_information_f4(app.logger(), "id:%d, keysn:%s, md5value:%s, sync:%b",
			syncRecord.id,
			syncRecord.keysn,
			syncRecord.md5,
			syncRecord.sync);

		if (syncRecord.md5 != _md5) {

			Statement update(session);
			update << "UPDATE syncSDMakeup set md5value = ?, sync = 0, modify_time = datetime('now','localtime') where keysn= ?;",
				use(_md5),
				use(syncRecord.keysn),
				sync,
				now;
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

	poco_information_f1(app.logger(), "check : %s\n ", Var(check).convert<std::string>());

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
		poco_information_f1(app.logger(), "%s", ds["fmt"].toString());
		std::string data = ds["fmt"].toString();
		URI uri(ds["url"]["sync"].toString());
		HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
		HTTPClientSession session(uri.getHost(), uri.getPort());
		request.setContentLength((int)data.length());
		session.sendRequest(request) << data;

		HTTPResponse response;
		std::istream& out = session.receiveResponse(response);
		DynamicStruct res = *extract<Object::Ptr>(out);
		poco_information_f2(app.logger(), "code:%s\n message:%s\n", res["code"].toString(), res["message"].toString());
		//assert(res["code"] == "0");
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
}