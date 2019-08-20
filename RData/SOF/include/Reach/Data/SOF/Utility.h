//
// Utility.h
//
// Library: Data/SOF
// Package: SOF
// Module:  Utility
//
// Definition of Utility.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SOF_Utility_INCLUDED
#define SOF_Utility_INCLUDED


#include "Reach/Data/SOF/SOF.h"
//#include "Reach/Data/MetaColumn.h"
#include "Poco/Bugcheck.h"
#include "Reach/Data/Session.h"
#include "Poco/Mutex.h"
#include "Poco/Types.h"
#include <map>

namespace Reach {
namespace Data {
namespace SOF {


class SOF_API Utility
	/// Various utility functions for SOF.
{
public:

	static void* dbHandle(const Session& session);
		/// Returns native DB handle.

	static std::string lastError(const std::string& containerName);
		/// Retreives the last error code from sqlite and converts it to a string.

	static void throwException(const std::string& containerName, int rc, const std::string& addErrMsg = std::string());
		/// Throws for an error code the appropriate exception

	static std::string config(const std::string& name);
	
	static std::string GetCertVersion(const std::string & base64);

	static std::string GetCertVaildTime(const std::string & base64);

	static std::string toLocalTime(const std::string & time);

	static std::string GetCertOwnerID(const std::string & base64);

	static std::string toLegelID(const std::string & text, const std::string & pattern);

	static void selectEncryptMethod(const std::string & containerString);

	static void spiltEntries(const std::string& entries, std::string& containerString, std::string& userString);

	static int GetRandomSize();

	static void selectSignMethod(const std::string & containerString);

private:
	Utility();
		/// Maps SOF column declared types to Poco::Data types through
		/// static TypeMap member.
		/// 
		/// Note: SOF is type-agnostic and it is the end-user responsibility
		/// to ensure that column declared data type corresponds to the type of 
		/// data actually held in the database.
		/// 
		/// Column types are case-insensitive.

	Utility(const Utility&);
	Utility& operator = (const Utility&);

	//static TypeMap     _types;
	static Poco::Mutex _mutex;
	static int         _threadMode;
	static int		   _random_size;
};


} } } // namespace Reach::Data::SOF


#endif // SOF_Utility_INCLUDED
