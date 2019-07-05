#pragma once

#include "Poco/Net/AbstractHTTPRequestHandler.h"

namespace Reach {

	using Poco::Net::AbstractHTTPRequestHandler;

	class RedirectRequestHandler : public AbstractHTTPRequestHandler
	{
	public:
		void run()
		{
			response().redirect("http://www.fjreach.com/");
		}
	};
}