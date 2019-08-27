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
#include "KeyDigitalSignByP1RequestHandler.h"
#include "VerifyDigitalSignByP1RequestHandler.h"
#include "KeySignByP7RequestHandler.h"
#include "VerifySignByP7RequestHandler.h"
#include "EncryptFileRequestHandler.h"
#include "DecryptFileRequestHandler.h"
#include "KeyEncryptDataRequestHandler.h"
#include "KeyDecryptDataRequestHandler.h"
#include "KeyEncryptByDigitalEnvelopeRequestHandler.h"
#include "KeyDecryptByDigitalEnvelopeRequestHandler.h"
#include "extOpenDeviceRequestHandler.h"
#include "extCloseDeviceRequestHandler.h"

using namespace Reach;

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;


HTTPRequestHandler * Reach::RequestHandlerFactory::createRequestHandler(const HTTPServerRequest & request)
{

	if (request.getURI() == "/echoBody")
		return new EchoBodyRequestHandler;
	else if (request.getURI() == "/echoHeader")
		return new EchoHeaderRequestHandler;
	else if (request.getURI() == "/redirect")
		return new RedirectRequestHandler();
	else if (request.getURI() == "/auth")
		return new AuthRequestHandler();
	else if (request.getURI() == "/buffer")
		return new BufferRequestHandler();
	else if (request.getURI() == "/RS_ConfigParameters")
		return new ConfigParametersRequestHandler;
	else if (request.getURI() == "/RS_GetParameters")
		return new GetParametersRequestHandler;
	else if (request.getURI() == "/RS_GetUserList")
		return new GetUserListRequestHandler;
	else if (request.getURI() == "/RS_GetCertBase64String")
		return new GetCertBase64StringRequestHandler;
	else if (request.getURI() == "/RS_GetCertInfo")
		return new GetCertInfoRequestHandler;
	else if (request.getURI() == "/RS_GetCertInfoEx")
		return new GetCertInfoExRequestHandler;
	else if (request.getURI() == "/RS_VerifyIdentity")
		return new VerifyIdentityRequestHandler;
	else if (request.getURI() == "/RS_CertLogin")
		return new CertLoginRequestHandler;
	else if (request.getURI() == "/RS_ChangePassWd")
		return new ChangePassWdRequestHandler;
	else if (request.getURI() == "/RS_GetPinRetryCount")
		return new GetPinRetryCountRequestHandler;
	else if (request.getURI() == "/RS_KeyGetKeySn")
		return new KeyGetKeySnRequestHandler;
	else if (request.getURI() == "/RS_KeySignByP1")
		return new KeySignByP1RequestHandler;
	else if (request.getURI() == "/RS_VerifySignByP1")
		return new VerifySignByP1RequestHandler;
	else if (request.getURI() == "/RS_KeyDigitalSignByP1")
		return new KeyDigitalSignByP1RequestHandler;
	else if (request.getURI() == "/RS_VerifyDigitalSignByP1")
		return new VerifyDigitalSignByP1RequestHandler;
	else if (request.getURI() == "/RS_KeySignByP7")
		return new KeySignByP7RequestHandler;
	else if (request.getURI() == "/RS_VerifySignByP7")
		return new VerifySignByP7RequestHandler;
	else if (request.getURI() == "/RS_EncryptFile")
		return new EncryptFileRequestHandler;
	else if (request.getURI() == "/RS_DecryptFile")
		return new DecryptFileRequestHandler;
	else if (request.getURI() == "/RS_KeyEncryptData")
		return new KeyEncryptDataRequestHandler;
	else if (request.getURI() == "/RS_KeyDecryptData")
		return new KeyDecryptDataRequestHandler;
	else if (request.getURI() == "/RS_KeyEncryptByDigitalEnvelope")
		return new KeyEncryptByDigitalEnvelopeRequestHandler;
	else if (request.getURI() == "/RS_KeyDecryptByDigitalEnvelope")
		return new KeyDecryptByDigitalEnvelopeRequestHandler;
	else if (request.getURI() == "/SOF_OpenDevice")
		return new extOpenDeviceRequestHandler;
	else if (request.getURI() == "/SOF_CloseDevice")
		return new extCloseDeviceRequestHandler;

		return 0;
}
