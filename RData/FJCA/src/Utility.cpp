//
// Utility.cpp
//
// Library: Data/FJCA
// Package: FJCA
// Module:  Utility
//
// Implementation of Utility
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Reach/Data/FJCA/Utility.h"
#include "Reach/Data/FJCA/FJCAException.h"
#include "Reach/Data/FJCA/translater.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/String.h"
#include "Poco/Any.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"
#include "Poco/RegularExpression.h"
#include "Poco/Debugger.h"

#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTime.h"
#include "Poco/Timezone.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "GMCrypto.h"
#include "SoFProvider.h"
#include "SOFErrorCode.h"
#include "Poco/Mutex.h"
#include "Poco/Tuple.h"

using Poco::RegularExpression;
using Poco::Timezone;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeParser;
using Poco::DateTimeFormatter;
using Poco::LocalDateTime;
using Poco::Debugger;
using Poco::format;
using Poco::replace;
using Poco::Util::Application;
using Poco::Path;


#ifndef FJCA_OPEN_URI
#define FJCA_OPEN_URI 0
#endif


namespace Reach {
namespace Data {
namespace FJCA {

//Utility::TypeMap Utility::_types;
Poco::Mutex Utility::_mutex;
int Utility::_random_size = 0;

Utility::Utility()
{
	/*
	if (_types.empty())
	{
		_types.insert(TypeMap::value_type("", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("BOOL", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("BOOLEAN", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("BIT", MetaColumn::FDT_BOOL));
		_types.insert(TypeMap::value_type("UINT8", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("UTINY", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("UINTEGER8", MetaColumn::FDT_UINT8));
		_types.insert(TypeMap::value_type("INT8", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("TINY", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("INTEGER8", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("UINT16", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("USHORT", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("UINTEGER16", MetaColumn::FDT_UINT16));
		_types.insert(TypeMap::value_type("INT16", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("SHORT", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("INTEGER16", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("UINT", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("UINT32", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("UINTEGER", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("UINTEGER32", MetaColumn::FDT_UINT32));
		_types.insert(TypeMap::value_type("INT", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("INT32", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("INTEGER", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("INTEGER32", MetaColumn::FDT_INT32));
		_types.insert(TypeMap::value_type("UINT64", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("ULONG", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("UINTEGER64", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("INT64", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("LONG", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("INTEGER64", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("TINYINT", MetaColumn::FDT_INT8));
		_types.insert(TypeMap::value_type("SMALLINT", MetaColumn::FDT_INT16));
		_types.insert(TypeMap::value_type("BIGINT", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("LONGINT", MetaColumn::FDT_INT64));
		_types.insert(TypeMap::value_type("COUNTER", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("AUTOINCREMENT", MetaColumn::FDT_UINT64));
		_types.insert(TypeMap::value_type("REAL", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("FLOA", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("FLOAT", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DOUB", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DOUBLE", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("DECIMAL", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("NUMERIC", MetaColumn::FDT_DOUBLE));
		_types.insert(TypeMap::value_type("CHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("CLOB", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("TEXT", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("VARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NCLOB", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NTEXT", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("NVARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("LONGVARCHAR", MetaColumn::FDT_STRING));
		_types.insert(TypeMap::value_type("BLOB", MetaColumn::FDT_BLOB));
		_types.insert(TypeMap::value_type("DATE", MetaColumn::FDT_DATE));
		_types.insert(TypeMap::value_type("TIME", MetaColumn::FDT_TIME));
		_types.insert(TypeMap::value_type("DATETIME", MetaColumn::FDT_TIMESTAMP));
		_types.insert(TypeMap::value_type("TIMESTAMP", MetaColumn::FDT_TIMESTAMP));
	}
	*/
}

std::string Utility::config(const std::string& name)
{
	Application& app = Application::instance();

	std::string appName = Path(app.commandPath()).getFileName();
	std::string fullpath = replace(app.commandPath(), appName, std::string(""));

	Path filePath(fullpath, name);

	return filePath.toString();
}

std::string Utility::lastError(const std::string& containerName)
{
	std::string errStr;
	Poco::Mutex::ScopedLock lock(_mutex); ;
	int rc = SOF_GetLastError();
	errStr = translater::default().tr("SOFError", rc);
	return errStr;
}


void Utility::throwException(const std::string& containerName, int rc, const std::string& addErrMsg)
{
	/*
	switch (rc)
	{
	case SOF_OK:
		break;
	case SOF_ERROR:
		throw InvalidSQLStatementException(lastError(pDB), addErrMsg);
	case SOF_INTERNAL:
		throw InternalDBErrorException(lastError(pDB), addErrMsg);
	case SOF_PERM:
		throw DBAccessDeniedException(lastError(pDB), addErrMsg);
	case SOF_ABORT:
		throw ExecutionAbortedException(lastError(pDB), addErrMsg);
	case SOF_BUSY:
	case SOF_BUSY_RECOVERY:
#if defined(SOF_BUSY_SNAPSHOT)
	case SOF_BUSY_SNAPSHOT:
#endif
		throw DBLockedException(lastError(pDB), addErrMsg);
	case SOF_LOCKED:
		throw TableLockedException(lastError(pDB), addErrMsg);
	case SOF_NOMEM:
		throw NoMemoryException(lastError(pDB), addErrMsg);
	case SOF_READONLY:
		throw ReadOnlyException(lastError(pDB), addErrMsg);
	case SOF_INTERRUPT:
		throw InterruptException(lastError(pDB), addErrMsg);
	case SOF_IOERR:
		throw IOErrorException(lastError(pDB), addErrMsg);
	case SOF_CORRUPT:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_NOTFOUND:
		throw TableNotFoundException(lastError(pDB), addErrMsg);
	case SOF_FULL:
		throw DatabaseFullException(lastError(pDB), addErrMsg);
	case SOF_CANTOPEN:
		throw CantOpenDBFileException(lastError(pDB), addErrMsg);
	case SOF_PROTOCOL:
		throw LockProtocolException(lastError(pDB), addErrMsg);
	case SOF_EMPTY:
		throw InternalDBErrorException(lastError(pDB), addErrMsg);
	case SOF_SCHEMA:
		throw SchemaDiffersException(lastError(pDB), addErrMsg);
	case SOF_TOOBIG:
		throw RowTooBigException(lastError(pDB), addErrMsg);
	case SOF_CONSTRAINT:
		throw ConstraintViolationException(lastError(pDB), addErrMsg);
	case SOF_MISMATCH:
		throw DataTypeMismatchException(lastError(pDB), addErrMsg);
	case SOF_MISUSE:
		throw InvalidLibraryUseException(lastError(pDB), addErrMsg);
	case SOF_NOLFS:
		throw OSFeaturesMissingException(lastError(pDB), addErrMsg);
	case SOF_AUTH:
		throw AuthorizationDeniedException(lastError(pDB), addErrMsg);
	case SOF_FORMAT:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_NOTADB:
		throw CorruptImageException(lastError(pDB), addErrMsg);
	case SOF_RANGE:
		throw InvalidSQLStatementException(lastError(pDB), addErrMsg);
	case SOF_ROW:
		break; // sqlite_step() has another row ready
	case SOF_DONE:
		break; // sqlite_step() has finished executing
	default:
		throw SOFException(Poco::format("Unknown error code: %d", rc), addErrMsg);
	}
	*/
}

std::string Utility::GetCertVersion(const std::string& base64)
{
	std::string item;
	item = SOF_GetCertInfo(base64, SGD_CERT_VERSION);

	///GB-T 20518-2006 信息安全技术 公钥基础设施 数字证书格式

	std::map<std::string, std::string> versions;
	versions["0"] = "V1";
	versions["1"] = "V2";
	versions["2"] = "V3";

	return versions[item];
}


std::string Utility::GetCertVaildTime(const std::string& base64)
{
	std::string item;
	item = SOF_GetCertInfo(base64, SGD_CERT_VALID_TIME);
	/// 190313160000Z - 210314155959Z
	int options = 0;
	std::string pattern("(\\S+)-(\\S+)");
	std::string vaildtime;

	try {

		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;
		if (!re.match(item, mtch))
			throw Poco::LogicException("GetCertVaildTime Exception!", 0x40);

		std::vector<std::string> tags;
		re.split(item, tags, options);

		std::string vaild_start = tags[1];
		std::string vaild_end = tags[2];
		Debugger::message(format("vaild_start : %s, vaild_start :%s", vaild_start, vaild_end));
		/// UTC to LocalTime +0800

		vaildtime.append(toLocalTime(vaild_start));
		vaildtime.append(" - ");
		vaildtime.append(toLocalTime(vaild_end));

		Debugger::message(format("vaildtime : %s", vaildtime));
	}
	catch (Poco::Exception&)
	{
	}

	return vaildtime;
}

std::string Utility::toLocalTime(const std::string& time)
{
	int options = 0;
	std::string pattern("^([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})([0-9]\\d{1})Z");
	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;
	if (!re.match(time, mtch))
		throw Poco::RegularExpressionException(100);
	///
	/// Match 1:	210314155959	     0	    12
	/// Group 1:	2103	     0	     4
	/// Group 2:	14	     4	     2
	/// Group 3:	15	     6	     2
	/// Group 4:	59	     8	     2
	/// Group 5:	59	    10	     2
	///
	std::vector<std::string> tags;
	re.split(time, tags, options);

	std::string prefix;
	int oct = std::stod(tags[1]);
	oct > 49 ? prefix = "19" : prefix = "20";
	std::string fmt = format("%s%s-%s-%s %s:%s", prefix, tags[1], tags[2], tags[3], tags[4], tags[5], tags[6]);

	Debugger::message(format("Timezone utcOffset: %d, tzd:: % d, name : %s", Timezone::utcOffset(), Timezone::tzd(), Timezone::name()));
	Debugger::message(time);
	int tzd = Timezone::tzd();
	DateTime dt = DateTimeParser::parse(DateTimeFormat::SORTABLE_FORMAT, fmt, tzd);
	LocalDateTime lt(dt);
	std::string localtime = DateTimeFormatter::format(lt, DateTimeFormat::SORTABLE_FORMAT);
	Debugger::message(localtime);
	return localtime;
}
std::string Utility::GetCertOwnerID(const std::string& base64)
{
	std::string item;
	std::string pattern("(\\d+[A-z]?)");
	std::string special_oid("1.2.156.10260.4.1.1");
	item = SOF_GetCertInfoByOid(base64, special_oid);
	if (item.empty()) {

		item = SOF_GetCertInfo(base64, SGD_CERT_SUBJECT_CN);
		pattern = format("@%s@", pattern);
	}

	item = toLegelID(item, pattern);
	/// erase 0 if is id card
	if (!item.empty() && item.at(0) == '0')
		item = item.replace(0, 1, "");

	return item;
}

std::string Utility::toLegelID(const std::string& text, const std::string& pattern)
{
	/// SGD_CERT_SUBJECT_CN identify card (330602197108300018)
	/// CN = 041@0330602197108300018@测试个人一@00000001
	/// 十八位：^[1-9]\d{5}(18|19|([23]\d))\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{3}[0-9Xx]$
	/// 十五位：^[1-9]\d{5}\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\d{2}[0-9Xx]$
	///RegularExpression pattern("@(\\d+)@");
	int options = 0;
	std::string id;

	try {
		RegularExpression re(pattern, options);
		RegularExpression::Match mtch;

		if (!re.match(text, mtch))
			throw Poco::LogicException("RS_KeyDecryptData uid Exception!", 0x40);

		std::vector<std::string> tags;
		re.split(text, tags, options);
		id = tags[1];
	}
	catch (Poco::Exception&)
	{

	}

	return id;
}



void Utility::selectEncryptMethod(const std::string& containerString)
{
	std::vector<std::string> methods;
	methods = SOF_GetDeviceCapability(containerString, 0);

	typedef Poco::Tuple<std::string, int, int> TupleType;
	typedef std::vector<TupleType> vTupleType;

	TupleType priority1("SGD_SM1_ECB", SGD_SM1_ECB, 16);
	TupleType priority2("SGD_SM1_CBC", SGD_SM1_CBC, 32);
	TupleType priority3("SGD_SM4_ECB", SGD_SM4_ECB, 16);
	TupleType priority4("SGD_SM4_CBC", SGD_SM4_CBC, 32);

	if (std::find(methods.begin(), methods.end(), priority1.get<0>()) != methods.end()) {
		SOF_SetEncryptMethod(priority1.get<1>());
		_random_size = priority1.get<2>();
	}
	else if (std::find(methods.begin(), methods.end(), priority2.get<0>()) != methods.end()) {
		SOF_SetEncryptMethod(priority2.get<1>());
		_random_size = priority2.get<2>();
	}
	else if (std::find(methods.begin(), methods.end(), priority3.get<0>()) != methods.end()) {
		SOF_SetEncryptMethod(priority3.get<1>());
		_random_size = priority3.get<2>();
	}
	else if (std::find(methods.begin(), methods.end(), priority4.get<0>()) != methods.end()) {
		SOF_SetEncryptMethod(priority4.get<1>());
		_random_size = priority4.get<2>();
	}
}

void Utility::spiltEntries(const std::string& entries, std::string& containerString, std::string& userString)
{
	std::string pattern("(\\S+)\\|\\|(\\S+)[&&&]*");
	int options = 0;

	RegularExpression re(pattern, options);
	RegularExpression::Match mtch;

	if (!re.match(entries, mtch)) {
		throw Poco::LogicException();
	}

	std::vector<std::string> tags;
	re.split(entries, tags, options);
	userString = tags[1];
	containerString = tags[2];
}

int Utility::GetRandomSize()
{
	return _random_size;
}

void Utility::selectSignMethod(const std::string& containerString)
{
	/// index from zero		1 - RSA Container Type
	/// (0 =>1)				2 - SM Container Type
	Poco::Tuple<std::string, std::string, int> dummy;
	dummy.set<0>("1");
	dummy.set<1>("RSA");
	dummy.set<2>(SGD_SHA1_RSA);

	Poco::Tuple<std::string, std::string, int> dummy2;
	dummy2.set<0>("2");
	dummy2.set<1>("SM2");
	dummy2.set<2>(SGD_SM3_SM2);

	std::string type = SOF_GetDeviceInfo(containerString, SGD_DEVICE_SUPPORT_ALG);

	if (dummy.get<0>() == type) {
		SOF_SetSignMethod(dummy.get<2>());
	}
	else if (dummy2.get<0>() == type) {
		SOF_SetSignMethod(dummy2.get<2>());
	}
}

// NOTE: Utility::dbHandle() has been moved to SessionImpl.cpp,
// as a workaround for a failing AnyCast with Clang.
// See <https://github.com/pocoproject/poco/issues/578>
// for a discussion.


} } } // namespace Poco::Data::FJCA
