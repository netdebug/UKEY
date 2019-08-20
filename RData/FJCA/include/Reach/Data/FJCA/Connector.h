//
// Connector.h
//
// Library: Data/FJCA
// Package: FJCA
// Module:  Connector
//
// Definition of the Connector class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RData_FJCA_Connector_INCLUDED
#define RData_FJCA_Connector_INCLUDED


#include "Reach/Data/FJCA/FJCA.h"
#include "Reach/Data/Connector.h"


namespace Reach {
namespace Data {
namespace FJCA {


class FJCA_API Connector: public Reach::Data::Connector
	/// Connector instantiates FJCA SessionImpl objects.
{
public:
	static const std::string KEY;
		/// Keyword for creating FJCA sessions ("sqlite").

	Connector();
		/// Creates the Connector.

	~Connector();
		/// Destroys the Connector.

	const std::string& name() const;
		/// Returns the name associated with this connector.

	Poco::AutoPtr<Reach::Data::SessionImpl> createSession(const std::string& connectionString,
		std::size_t timeout = Reach::Data::SessionImpl::LOGIN_TIMEOUT_DEFAULT);
		/// Creates a FJCA SessionImpl object and initializes it with the given connectionString.

	static void registerConnector();
		/// Registers the Connector under the Keyword Connector::KEY at the Poco::Data::SessionFactory.

	static void unregisterConnector();
		/// Unregisters the Connector under the Keyword Connector::KEY at the Poco::Data::SessionFactory.
};


///
/// inlines
///
inline const std::string& Connector::name() const
{
	return KEY;
}


} } } // namespace Poco::Data::FJCA


#endif // Data_FJCA_Connector_INCLUDED
