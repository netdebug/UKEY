#include "RequestHandlerFactory.h"
#include "EchoBodyRequestHandler.h"
#include "EchoHeaderRequestHandler.h"
#include "RedirectRequestHandler.h"
#include "AuthRequestHandler.h"
#include "BufferRequestHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "routes/ConfigParametersRequestHandler.h"
#include "routes/GetParametersRequestHandler.h"
#include "routes/GetUserListRequestHandler.h"
#include "routes/GetCertBase64StringRequestHandler.h"
#include "routes/GetCertInfoRequestHandler.h"
#include "routes/VerifyIdentityRequestHandler.h"
#include "routes/CertLoginRequestHandler.h"
#include "routes/ChangePassWdRequestHandler.h"
#include "routes/GetPinRetryCountRequestHandler.h"
#include "routes/KeyGetKeySnRequestHandler.h"
#include "routes/KeySignByP1RequestHandler.h"
#include "routes/VerifySignByP1RequestHandler.h"
#include "routes/VerifySignByP1ExtRequestHandler.h"
#include "routes/KeyDigitalSignByP1RequestHandler.h"
#include "routes/VerifyDigitalSignByP1RequestHandler.h"
#include "routes/KeySignByP7RequestHandler.h"
#include "routes/VerifySignByP7RequestHandler.h"
#include "routes/VerifySignByP7ExtRequestHandler.h"
#include "routes/EncryptFileRequestHandler.h"
#include "routes/DecryptFileRequestHandler.h"
#include "routes/KeyEncryptDataRequestHandler.h"
#include "routes/KeyDecryptDataRequestHandler.h"
#include "routes/KeyEncryptFileRequestHandler.h"
#include "routes/KeyDecryptFileRequestHandler.h"
#include "routes/KeyStatusRequestHandler.h"
#include "routes/KeyEncryptByDigitalEnvelopeRequestHandler.h"
#include "routes/KeyDecryptByDigitalEnvelopeRequestHandler.h"
#include "routes/CloudAPI/GetTransidRequestHandler.h"
#include "routes/CloudAPI/GreateQRCodeRequestHandler.h"
#include "routes/CloudAPI/CloudLoginAuthRequestHandler.h"
#include "routes/CloudAPI/CloudDevryptAuthRequestHandler.h"
#include "routes/CloudAPI/CloudDevryptDataRequestHandler.h"
#include "routes/CloudAPI/CloudDevryptFileRequestHandler.h"
#include "routes/CloudAPI/CloudEncryptAuthRequestHandler.h"
#include "routes/CloudAPI/CloudEncryptDataRequestHandler.h"
#include "routes/CloudAPI/CloudEncryptFileRequestHandler.h"
#include "routes/CloudAPI/CloudGetAuthRequestHandler.h"
#include "routes/CloudAPI/CloudGetCertAuthRequestHandler.h"
#include "routes/CloudAPI/CloudGetCertBase64RequestHandler.h"
#include "routes/CloudAPI/CloudGetCompanyCertRequestHandler.h"
#include "routes/CloudAPI/CloudGetSealListRequestHandler.h"
#include "routes/CloudAPI/CloudGetSignResultRequestHandler.h"
#include "routes/CloudAPI/CloudLoginAuthRequestHandler.h"
#include "routes/CloudAPI/CloudLogoutAuthRequestHandler.h"
#include "routes/CloudAPI/CloudLogoutRequestHandler.h"
#include "routes/CloudAPI/CloudReceiveDevryptResultRequestHandler.h"
#include "routes/CloudAPI/CloudSealAuthRequestHandler.h"
#include "routes/CloudAPI/CloudSignByP7RequestHandler.h"
#include "routes/CloudAPI/GetTransidRequestHandler.h"
#include "routes/CloudAPI/EncryptDataBase64RequestHandler.h"
#include "routes/CloudAPI/EncryptFileBase64RequestHandler.h"

using namespace Reach;

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;


HTTPRequestHandler * Reach::RequestHandlerFactory::createRequestHandler(const HTTPServerRequest & request)
{
	return new EncryptFileBase64RequestHandler;

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
	else if (request.getURI() == "/RS_VerifySignByP1Ext")
		return new VerifySignByP1ExtRequestHandler;
	else if (request.getURI() == "/RS_KeyDigitalSignByP1")
		return new KeyDigitalSignByP1RequestHandler;
	else if (request.getURI() == "/RS_VerifyDigitalSignByP1")
		return new VerifyDigitalSignByP1RequestHandler;
	else if (request.getURI() == "/RS_KeySignByP7")
		return new KeySignByP7RequestHandler;
	else if (request.getURI() == "/RS_VerifySignByP7")
		return new VerifySignByP7RequestHandler;
	else if (request.getURI() == "/RS_VerifySignByP7Ext")
		return new VerifySignByP7ExtRequestHandler;
	else if (request.getURI() == "/RS_EncryptFile")
		return new EncryptFileRequestHandler;
	else if (request.getURI() == "/RS_DecryptFile")
		return new DecryptFileRequestHandler;
	else if (request.getURI() == "/RS_KeyEncryptData")
		return new KeyEncryptDataRequestHandler;
	else if (request.getURI() == "/RS_KeyDecryptData")
		return new KeyDecryptDataRequestHandler;
	else if (request.getURI() == "/RS_KeyEncryptFile")
		return new KeyEncryptFileRequestHandler;
	else if (request.getURI() == "/RS_KeyDecryptFile")
		return new KeyDecryptFileRequestHandler;
	else if (request.getURI() == "/RS_KeyEncryptByDigitalEnvelope")
		return new KeyEncryptByDigitalEnvelopeRequestHandler;
	else if (request.getURI() == "/RS_KeyDecryptByDigitalEnvelope")
		return new KeyDecryptByDigitalEnvelopeRequestHandler;
	else if (request.getURI() == "/RS_KeyStatus")
		return new KeyStatusRequestHandler;
	else if (request.getURI() == "/RS_GetTransid")
		return new GetTransidRequestHandler;
	else if (request.getURI() == "/RS_GreateQRCode")
		return new GreateQRCodeRequestHandler;
	else if (request.getURI() == "/RS_CloudLoginAuth")
		return new CloudLoginAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudDevryptAuth")
		return new CloudDevryptAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudDevryptData")
		return new CloudDevryptDataRequestHandler;
	else if (request.getURI() == "/RS_CloudDevryptFile")
		return new CloudDevryptFileRequestHandler;
	else if (request.getURI() == "/RS_CloudEncryptAuth")
		return new CloudEncryptAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudEncryptData")
		return new CloudEncryptDataRequestHandler;
	else if (request.getURI() == "/RS_CloudEncryptFile")
		return new CloudEncryptFileRequestHandler;
	else if (request.getURI() == "/RS_CloudGetAuth")
		return new CloudGetAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudGetCertAuth")
		return new CloudGetCertAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudGetCertBase64")
		return new CloudGetCertBase64RequestHandler;
	else if (request.getURI() == "/RS_CloudGetCompanyCert")
		return new CloudGetCompanyCertRequestHandler;
	else if (request.getURI() == "/RS_CloudGetSealList")
		return new CloudGetSealListRequestHandler;
	else if (request.getURI() == "/RS_CloudGetSignResult")
		return new CloudGetSignResultRequestHandler;
	else if (request.getURI() == "/RS_CloudLogoutAuth")
		return new CloudLogoutAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudLogout")
		return new CloudLogoutRequestHandler;
	else if (request.getURI() == "/RS_CloudReceiveDevryptResult")
		return new CloudReceiveDevryptResultRequestHandler;
	else if (request.getURI() == "/RS_CloudSealAuth")
		return new CloudSealAuthRequestHandler;
	else if (request.getURI() == "/RS_CloudSignByP7")
		return new CloudSignByP7RequestHandler;
	else if (request.getURI() == "/RS_EncryptData")
		return new EncryptDataBase64RequestHandler;
	else if (request.getURI() == "/RS_EncryptFile")
		return new EncryptFileBase64RequestHandler;
		return 0;
}
