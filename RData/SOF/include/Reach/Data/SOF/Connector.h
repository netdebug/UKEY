//
// Connector.h
//
// Library: Data/SOF
// Package: SOF
// Module:  Connector
//
// Definition of the Connector class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef RData_SOF_Connector_INCLUDED
#define RData_SOF_Connector_INCLUDED


#include "Reach/Data/SOF/SOF.h"
#include "Reach/Data/Connector.h"


namespace Reach {
namespace Data {
namespace SOF {


class SOF_API Connector: public Reach::Data::Connector
	/// Connector instantiates SOF SessionImpl objects.
{
public:
	static const std::string KEY;
		/// Keyword for creating SOF sessions ("sqlite").

	Connector();
		/// Creates the Connector.

	~Connector();
		/// Destroys the Connector.

	const std::string& name() const;
		/// Returns the name associated with this connector.

	Poco::AutoPtr<Reach::Data::SessionImpl> createSession(const std::string& connectionString,
		std::size_t timeout = Reach::Data::SessionImpl::LOGIN_TIMEOUT_DEFAULT);
		/// Creates a SOF SessionImpl object and initializes it with the given connectionString.

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


} } } // namespace Poco::Data::SOF


#endif // Data_SOF_Connector_INCLUDED
