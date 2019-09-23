#include "RequestHandlerFactory.h"
#include "EchoBodyRequestHandler.h"
#include "EchoHeaderRequestHandler.h"
#include "RedirectRequestHandler.h"
#include "AuthRequestHandler.h"
#include "BufferRequestHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "ConfigParametersRequestHandler.h"
#include "GetParametersRequestHandler.h"
#include "GetUserListRequestHandler.h"
#include "GetCertBase64StringRequestHandler.h"
#include "GetCertInfoRequestHandler.h"
#include "GetCertInfoExRequestHandler.h"
#include "VerifyIdentityRequestHandler.h"
#include "CertLoginRequestHandler.h"
#include "ChangePassWdRequestHandler.h"
#include "GetPinRetryCountRequestHandler.h"
#include "KeyGetKeySnRequestHandler.h"
#include "KeySignByP1RequestHandler.h"
#include "VerifySignByP1RequestHandler.h"
#include "VerifySignByP1ExtRequestHandler.h"
#include "KeyDigitalSignByP1RequestHandler.h"
#include "VerifyDigitalSignByP1RequestHandler.h"
#include "KeySignByP7RequestHandler.h"
#include "VerifySignByP7RequestHandler.h"
#include "VerifySignByP7ExtRequestHandler.h"
#include "EncryptFileRequestHandler.h"
#include "DecryptFileRequestHandler.h"
#include "KeyEncryptDataRequestHandler.h"
#include "KeyDecryptDataRequestHandler.h"
#include "KeyEncryptByDigitalEnvelopeRequestHandler.h"
#include "KeyDecryptByDigitalEnvelopeRequestHandler.h"
#include "extOpenDeviceRequestHandler.h"
#include "extCloseDeviceRequestHandler.h"
#include "Poco/String.h"
#include "Poco/URI.h"

using namespace Reach;

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::isubstr;
using Poco::URI;

HTTPRequestHandler * Reach::RequestHandlerFactory::createRequestHandler(const HTTPServerRequest & request)
{
	URI uri(request.getURI());
	poco_information_f1(Application::instance().logger(), "uri from %s", uri.getPath());

	if (uri.getPath() == "/echoBody")
		return new EchoBodyRequestHandler;
	else if (uri.getPath() == "/echoHeader")
		return new EchoHeaderRequestHandler;
	else if (uri.getPath() == "/redirect")
		return new RedirectRequestHandler();
	else if (uri.getPath() == "/auth")
		return new AuthRequestHandler();
	else if (uri.getPath() == "/buffer")
		return new BufferRequestHandler();
	else if (uri.getPath() == "/RS_ConfigParameters")
		return new ConfigParametersRequestHandler;
	else if (uri.getPath() == "/RS_GetParameters")
		return new GetParametersRequestHandler;
	else if (uri.getPath() == "/RS_GetUserList")
		return new GetUserListRequestHandler;
	else if (uri.getPath() == "/RS_GetCertBase64String")
		return new GetCertBase64StringRequestHandler;
	else if (uri.getPath() == "/RS_GetCertInfo")
		return new GetCertInfoRequestHandler;
	else if (uri.getPath() == "/RS_GetCertInfoEx")
		return new GetCertInfoExRequestHandler;
	else if (uri.getPath() == "/RS_VerifyIdentity")
		return new VerifyIdentityRequestHandler;
	else if (uri.getPath() == "/RS_CertLogin")
		return new CertLoginRequestHandler;
	else if (uri.getPath() == "/RS_ChangePassWd")
		return new ChangePassWdRequestHandler;
	else if (uri.getPath() == "/RS_GetPinRetryCount")
		return new GetPinRetryCountRequestHandler;
	else if (uri.getPath() == "/RS_KeyGetKeySn")
		return new KeyGetKeySnRequestHandler;
	else if (uri.getPath() == "/RS_KeySignByP1")
		return new KeySignByP1RequestHandler;
	else if (uri.getPath() == "/RS_VerifySignByP1")
		return new VerifySignByP1RequestHandler;
	else if (uri.getPath() == "/RS_VerifySignByP1Ext")
		return new VerifySignByP1ExtRequestHandler;
	else if (uri.getPath() == "/RS_KeyDigitalSignByP1")
		return new KeyDigitalSignByP1RequestHandler;
	else if (uri.getPath() == "/RS_VerifyDigitalSignByP1")
		return new VerifyDigitalSignByP1RequestHandler;
	else if (uri.getPath() == "/RS_KeySignByP7")
		return new KeySignByP7RequestHandler;
	else if (uri.getPath() == "/RS_VerifySignByP7")
		return new VerifySignByP7RequestHandler;
	else if (uri.getPath() == "/RS_VerifySignByP7Ext")
		return new VerifySignByP7ExtRequestHandler;
	else if (uri.getPath() == "/RS_EncryptFile")
		return new EncryptFileRequestHandler;
	else if (uri.getPath() == "/RS_DecryptFile")
		return new DecryptFileRequestHandler;
	else if (uri.getPath() == "/RS_KeyEncryptData")
		return new KeyEncryptDataRequestHandler;
	else if (uri.getPath() == "/RS_KeyDecryptData")
		return new KeyDecryptDataRequestHandler;
	else if (uri.getPath() == "/RS_KeyEncryptByDigitalEnvelope")
		return new KeyEncryptByDigitalEnvelopeRequestHandler;
	else if (uri.getPath() == "/RS_KeyDecryptByDigitalEnvelope")
		return new KeyDecryptByDigitalEnvelopeRequestHandler;
	else if (uri.getPath() == "/SOF_OpenDevice")
		return new extOpenDeviceRequestHandler;
	else if (uri.getPath() == "/SOF_CloseDevice")
		return new extCloseDeviceRequestHandler;

		return 0;
}
