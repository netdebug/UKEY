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
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "OESSealProvider.h"
#include "XSSealProvider.h"
#include "KGSealProvider.h"
#include "FJCAMedia.h"
#include "SOFMedia.h"
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
using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::MD5Engine;
using Poco::DigestEngine;

QZSyncWorker::QZSyncWorker()
	:Task("QZSyncWorker"),
	session("SQLite", "syncQLite.db")
{
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

void QZSyncWorker::extractKeyInfo()
{
	typedef std::vector<Poco::AutoPtr<MediaBase>> SPVec;
	typedef std::vector<Poco::AutoPtr<MediaBase>>::iterator SPIter;
	SPVec media;
	media.push_back(new FJCAMedia);
	media.push_back(new SOFMedia);

	for (SPIter it = media.begin(); it != media.end(); it++) {
		try 
		{
			(*it)->extract();
			_cert = (*it)->getProperty("cert");
			_keysn = (*it)->getProperty("keysn");
			_validStart = (*it)->getProperty("validStart");
			_validEnd = (*it)->getProperty("validEnd");
			break;
		}
		catch (Poco::Exception& e)
		{
			std::string message(format("QZSyncWorker Composite Exception %[1]d : %[0]s", e.message(), e.code()));
			log(message);
		}
	}
}

void QZSyncWorker::extractSealData()
{
	typedef std::vector<Poco::AutoPtr<SealProvider>> SPVec;
	typedef std::vector<Poco::AutoPtr<SealProvider>>::iterator SPIter;
	SPVec oess;
	oess.push_back(new OESSealProvider);
	oess.push_back(new XSSealProvider);
	oess.push_back(new KGSealProvider);

	for (SPIter it = oess.begin(); it != oess.end(); it++) {
		try
		{
			(*it)->extract(_cert);
			_name = (*it)->getProperty("name");
			_seals = (*it)->getProperty("seals");

			break;
		}
		catch (Poco::Exception& e)
		{
			std::string message(format("QZSyncWorker Composite Exception %[1]d : %[0]s", e.message(), e.code()));
			log(message);
		}
	}
}

void QZSyncWorker::GeneratedMD5()
{
	MD5Engine md5;
	DigestOutputStream ds(md5);
	ds << _keysn
		<< "&&"
		<< _seals;
	ds.close();

	_md5 = DigestEngine::digestToHex(md5.digest());
}

void QZSyncWorker::GeneratedCode()
{
	UUIDGenerator& gen = UUIDGenerator::defaultGenerator();
	UUID uuid = gen.createFromName(UUID::uri(), _keysn);
	_code = uuid.toString();
}


void QZSyncWorker::composite()
{
	Application& app = Application::instance();

	extractKeyInfo();
	extractSealData();
	GeneratedMD5();
	GeneratedCode();

	std::string message;
	message.append(format("name:%s,code%:%s \n", _name, _code));
	message.append(format("validStart:%s,validEnd%:%s\n", _validStart, _validEnd));
	message.append(format("keysn:%s,dataMD5%:%s\n", _keysn, _md5));
	message.append(format("seal -> \n%s", _seals));
	log(message);
}

void QZSyncWorker::updateStatus()
{
	/// | Title		 |	T	|	F	|	T	|	F	|
	/// | MD5		 |	1	|	1	|	0	|	0	|
	/// | sync		 |	1	|	0	|	1	|	0	|
	///	| transfer   |	No	|	Yes	|	Yes	|	YES	|
	/// | Final		 |		|	Y	|		|		|
	///
	///	SQLITE syntax:
	/// CREATE TABLE syncSDMakeup (id integer primary key, keysn VARCHAR(32), md5value VARCHAR(32),
	/// sync BOOLEAN DEFAULT 0, create_time datetime DEFAULT (datetime('now','localtime')), 
	/// modify_time datetime DEFAULT (datetime('now','localtime'))
	/// );
	Application& app = Application::instance();

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

			log(format("[insert SQL Statement :%s], keysn=%s, md5value=%s", insert.toString(), _keysn, _md5));

			break;
		}

		log(format("[select SQL Statement :%s ],keysn= %s, md5value=%s, sync = %b", select.toString(), syncRecord.keysn, syncRecord.md5, syncRecord.sync));

		if (syncRecord.md5 != _md5) {

			Statement update(session);
			update << "UPDATE syncSDMakeup set md5value = ?, sync = 0, modify_time = datetime('now','localtime') where keysn= ?;",
				use(_md5),
				use(syncRecord.keysn),
				sync,
				now;

			log(format("[update SQL Statement :%s] when the md5 is different, keysn=%s, md5value=%s sync = 0", update.toString(), syncRecord.keysn, _md5));
		}
	}
}

bool QZSyncWorker::checkFromServer()
{
	DynamicStruct ds = *object;

	Object check;
	check.set("appcode", ds["fmt"]["appcode"].toString());
	check.set("keysn", _keysn);
	check.set("dataMD5", _md5);

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

	log(format("checking code:%s message:%s\n", res["code"].toString(), res["message"].toString()));

	if (res["code"] == "1" || res["code"] == "6")
		setSync(_keysn);

	return (res["code"] == "0" || res["code"] == "7");
}

void QZSyncWorker::sendToServer()
{
	DynamicStruct ds = *object;

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
	//log(format("transfer code:%s message:%s\n", res["code"].toString(), res["message"].toString()));

	if (res["code"] != "0" && res["code"] != "10")
		throw Poco::LogicException("transfer failed!", res.toString());
}

void QZSyncWorker::transfer()
{
	if (checkFromServer())
	{
		sendToServer();
		setSync(_keysn);
	}
}

void QZSyncWorker::setSync(std::string& keysn, bool flag)
{
	Application& app = Application::instance();

	Statement select(session);
	select << "UPDATE syncSDMakeup set sync = ? WHERE keysn = ?;",
		use(flag), use(keysn), range(0, 1), sync, now;

	log(format("[setSync SQL Statement :%s] keysn=%s, sync=%b", select.toString(), keysn, flag));
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
	OutputDebugStringA(Utility::UTF8EncodingGBK(ostr.str()).c_str());
}