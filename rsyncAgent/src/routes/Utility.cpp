#include "Utility.h"
#include "Poco/Exception.h"
#include "Reach/Data/SessionHolder.h"
#include "Poco/SingletonHolder.h"
#include "Poco/Util/Application.h"
#include "Poco/Path.h"
#include "Poco/String.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/Random.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Struct.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/StreamCopier.h"
#include <cassert>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"

using namespace Reach;
using Poco::SingletonHolder;
using Reach::Data::SessionContainer;
using Poco::format;
using Poco::replace;
using Poco::Path;
using Poco::Random;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::Util::Application;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::DynamicStruct;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPClientSession;
using Poco::StreamCopier;
using Poco::HexBinaryEncoder;
using Poco::HexBinaryDecoder;
using namespace Poco::Dynamic;

extern std::string SOF_GetCertInfoByOid(std::string Base64EncodeCert, std::string oid);

Utility::~Utility()
{

}

std::string Utility::SOF_GenRandom(int size)
{
	throw Poco::NotImplementedException("SOF_GenRandom");
	return "";
}

bool Utility::SOF_EncryptFile(std::string&, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_EncryptFile");
	return false;
}

std::string Utility::SOF_ExportExChangeUserCert(const std::string&)
{
	throw Poco::NotImplementedException("SOF_ExportExChangeUserCert");
	return "";
}

std::string Utility::SOF_AsDecrypt(std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_AsDecrypt");
	return "";
}

std::string Utility::SOF_AsEncrypt(std::string &, std::string &)
{
	throw Poco::NotImplementedException("SOF_AsEncrypt");
	return "";
}

bool Utility::SOF_DecryptFile(std::string&, std::string, std::string)
{
	throw Poco::NotImplementedException("SOF_DecryptFile");
	return false;
}

int Utility::random()
{
	throw Poco::NotImplementedException("random");
	return 16;
}

int Utility::SOF_GetPinRetryCount(const std::string&)
{
	throw Poco::NotImplementedException("SOF_GetPinRetryCount");
	return 0;
}

std::string Utility::SOF_SignMessage(short, std::string&, std::string&)
{
	throw Poco::NotImplementedException("SOF_SignMessage");
	return "";
}

bool Utility::SOF_VerifySignedMessage(const std::string&, const std::string&)
{
	throw Poco::NotImplementedException("SOF_VerifySignedMessage");
	return false;
}

int Utility::SOF_GetLastError()
{
	return 0xA000001;
}

std::string Utility::GetCertInfoByOid(const std::string& cer, const std::string& oid)
{
	throw Poco::NotImplementedException("GetCertInfoByOid");
	return "";
}

namespace
{
	static SingletonHolder<SessionContainer> sh;
}

SessionContainer& Utility::getSC()
{
	return *sh.get();
}

Session Utility::getSession()
{
	Application& app = Application::instance();
	std::string scheme = app.config().getString("engine.mode", "");
	std::string uri = Poco::format("%s:///REST",scheme);
	return Utility::getSC().get(uri);
}

std::string Utility::config(const std::string& name)
{
	Application& app = Application::instance();

	std::string appName = Path(app.commandPath()).getFileName();
	std::string fullpath = replace(app.commandPath(), appName, std::string(""));

	Path filePath(fullpath, name);

	return filePath.toString();
}

std::string Utility::timestamp()
{
	Poco::Timestamp ts;
	ts.update();
	return DateTimeFormatter::format(ts, "%Y%m%d%H%M%S%i");
}

std::string Utility::UniqueTransOrder()
{
	std::string TRANSID;

	Random rnd(Random::RND_STATE_128);
	rnd.seed();

	format(TRANSID, "%s%u", timestamp(), rnd.next());

	return TRANSID;
}

bool Utility::resultFormLocal(const std::string& json)
{
	return result(json, "code");
}

bool Utility::resultFormNet(const std::string& json)
{
	return result(json, "RESULTCODE");
}

bool Utility::result(const std::string& json, const std::string& key)
{
	Parser C;
	Var v = C.parse(json);
	Object::Ptr object = v.extract<Object::Ptr>();
	DynamicStruct ds = *object;

	assert(ds.contains(key));
	return (ds[key] == "0000");
}

bool Utility::testJSON(const std::string& buffer)
{
	try
	{
		Parser C;
		Var result = C.parse(buffer);
		return true;
	}
	catch (Poco::JSON::JSONException& jsone)
	{
		std::cout << jsone.message() << std::endl;
	}
	return false;
}

std::string Utility::cat(const std::string& delim, std::size_t pos, const std::string& str)
{
	assert(pos < str.length());

	std::string result;

	for (int i = 0; i < str.length(); i++)
	{
		result.push_back(str[i]);
		if (i > 0 && i % pos == 0) result.append(delim);
	}
	result.append(delim);
	return result;
}

std::string Utility::sendRequest(const std::string& url, const std::string& data)
{
	Application& app = Application::instance();

	Poco::URI uri(url);

	HTTPRequest request(HTTPRequest::HTTP_POST, uri.getPath());
	request.setContentLength((int)data.length());
	request.setContentType("application/json");
	HTTPClientSession session(uri.getHost(), uri.getPort());
	session.sendRequest(request) << data;
	poco_information_f3(app.logger(), "session : %s:%hu %s", uri.getHost(), uri.getPort(), uri.getPath());

	HTTPResponse response;
	std::istream& out = session.receiveResponse(response);
	std::ostringstream ostr;
	StreamCopier::copyStream(out, ostr);

	return ostr.str();
}

std::string Utility::v_encrypt_by_sm2(const std::string& plaintext, const std::string& pubkey)
{
	Application& app = Application::instance();

	std::istringstream istr(pubkey);
	std::string skey;
	HexBinaryDecoder decoder(istr);
	int c = decoder.get();
	while (c != -1) { skey += char(c); c = decoder.get(); }

	poco_information_f1(app.logger(), "%s", skey);

	unsigned char c1[65], c3[32] = { 0 };
	unsigned char *c2 = nullptr;

	size_t length = plaintext.size();
	if (!(c2 = (unsigned char *)malloc(length)))
		throw Poco::OutOfMemoryException();

	if (sm2_encrypt((unsigned char*)plaintext.data(), plaintext.size(), (unsigned char*)skey.data(), c1, c3, c2) && c2)
		throw Poco::LogicException("sm2 cipher failed!");

	std::ostringstream ostr;
	HexBinaryEncoder encoder(ostr);
	encoder.rdbuf()->setLineLength(0);
	encoder.write((const char*)c1, sizeof(c1));
	encoder.write((const char*)c3, sizeof(c3));
	encoder.write((const char*)c2, length);

	poco_information_f1(app.logger(), "%s", ostr.str());
	std::string ciphertext = Poco::toUpper(ostr.str());
	return ciphertext;
}

int Utility::sm2_encrypt(const unsigned char *message, const int message_len, const unsigned char *pub_key, unsigned char *c1, unsigned char *c3, unsigned char *c2)
{
	//生成密钥对错误代码
#define CREATE_SM2_KEY_PAIR_FAIL     0x1002
#define ALLOCATION_MEMORY_FAIL       0x1004
//加解密错误代码
#define INVALID_NULL_VALUE_INPUT     0x1000
#define INVALID_INPUT_LENGTH         0x1001
#define COMPUTE_SM3_DIGEST_FAIL      0x1003
#define COMPUTE_SM2_SIGNATURE_FAIL   0x1005
#define INVALID_SM2_SIGNATURE        0x1006
#define VERIFY_SM2_SIGNATURE_FAIL    0x1007
#define EC_POINT_IS_AT_INFINITY      0x1008
#define COMPUTE_SM2_CIPHERTEXT_FAIL  0x1009
#define COMPUTE_SM2_KDF_FAIL         0x100a
#define INVALID_SM2_CIPHERTEXT       0x100b
#define SM2_DECRYPT_FAIL             0x100c

	int error_code;
	unsigned char pub_key_x[32], pub_key_y[32], c1_x[32], c1_y[32], x2[32], y2[32];
	unsigned char c1_point[65], x2_y2[64];
	unsigned char *t = NULL;
	BN_CTX *ctx = NULL;
	BIGNUM *bn_k = NULL, *bn_c1_x = NULL, *bn_c1_y = NULL;
	BIGNUM *bn_pub_key_x = NULL, *bn_pub_key_y = NULL;
	BIGNUM *bn_x2 = NULL, *bn_y2 = NULL;
	const BIGNUM *bn_order, *bn_cofactor;
	EC_GROUP *group = NULL;
	const EC_POINT *generator;
	EC_POINT *pub_key_pt = NULL, *c1_pt = NULL, *s_pt = NULL, *ec_pt = NULL;
	const EVP_MD *md;
	EVP_MD_CTX *md_ctx = NULL;
	int i, flag;

	memcpy(pub_key_x, (pub_key + 1), sizeof(pub_key_x));
	memcpy(pub_key_y, (pub_key + 1 + sizeof(pub_key_x)), sizeof(pub_key_y));

	error_code = ALLOCATION_MEMORY_FAIL;
	if (!(t = (unsigned char *)malloc(message_len)))
	{
		goto clean_up;
	}
	if (!(ctx = BN_CTX_new()))
	{
		goto clean_up;
	}
	BN_CTX_start(ctx);
	bn_k = BN_CTX_get(ctx);
	bn_c1_x = BN_CTX_get(ctx);
	bn_c1_y = BN_CTX_get(ctx);
	bn_pub_key_x = BN_CTX_get(ctx);
	bn_pub_key_y = BN_CTX_get(ctx);
	bn_x2 = BN_CTX_get(ctx);
	bn_y2 = BN_CTX_get(ctx);
	if (!(bn_y2))
	{
		goto clean_up;
	}
	if (!(group = EC_GROUP_new_by_curve_name(NID_sm2)))
	{
		goto clean_up;
	}

	if (!(pub_key_pt = EC_POINT_new(group)))
	{
		goto clean_up;
	}
	if (!(c1_pt = EC_POINT_new(group)))
	{
		goto clean_up;
	}
	if (!(s_pt = EC_POINT_new(group)))
	{
		goto clean_up;
	}
	if (!(ec_pt = EC_POINT_new(group)))
	{
		goto clean_up;
	}

	if (!(md_ctx = EVP_MD_CTX_new()))
	{
		goto clean_up;
	}

	error_code = COMPUTE_SM2_CIPHERTEXT_FAIL;
	if (!(BN_bin2bn(pub_key_x, sizeof(pub_key_x), bn_pub_key_x)))
	{
		goto clean_up;
	}
	if (!(BN_bin2bn(pub_key_y, sizeof(pub_key_y), bn_pub_key_y)))
	{
		goto clean_up;
	}

	if (!(bn_order = EC_GROUP_get0_order(group)))
	{
		goto clean_up;
	}
	if (!(bn_cofactor = EC_GROUP_get0_cofactor(group)))
	{
		goto clean_up;
	}
	if (!(generator = EC_GROUP_get0_generator(group)))
	{
		goto clean_up;
	}

	if (!(EC_POINT_set_affine_coordinates_GFp(group,
		pub_key_pt,
		bn_pub_key_x,
		bn_pub_key_y,
		ctx)))
	{
		goto clean_up;
	}

	/* Compute EC point s = [h]Pubkey, h is the cofactor.
	   If s is at infinity, the function returns and reports an error. */
	if (!(EC_POINT_mul(group, s_pt, NULL, pub_key_pt, bn_cofactor, ctx)))
	{
		goto clean_up;
	}
	if (EC_POINT_is_at_infinity(group, s_pt))
	{
		error_code = EC_POINT_IS_AT_INFINITY;
		goto clean_up;
	}
	md = EVP_sm3();

	do
	{
		if (!(BN_rand_range(bn_k, bn_order)))
		{
			goto clean_up;
		}
		if (BN_is_zero(bn_k))
		{
			continue;
		}
		if (!(EC_POINT_mul(group, c1_pt, bn_k, NULL, NULL, ctx)))
		{
			goto clean_up;
		}
		if (!(EC_POINT_mul(group, ec_pt, NULL, pub_key_pt, bn_k, ctx)))
		{
			goto clean_up;
		}
		if (!(EC_POINT_get_affine_coordinates_GFp(group,
			ec_pt,
			bn_x2,
			bn_y2,
			ctx)))
		{
			goto clean_up;
		}
		if (BN_bn2binpad(bn_x2,
			x2,
			sizeof(x2)) != sizeof(x2))
		{
			goto clean_up;
		}
		if (BN_bn2binpad(bn_y2,
			y2,
			sizeof(y2)) != sizeof(y2))
		{
			goto clean_up;
		}
		memcpy(x2_y2, x2, sizeof(x2));
		memcpy((x2_y2 + sizeof(x2)), y2, sizeof(y2));

		if (!(ECDH_KDF_X9_62(t,
			message_len,
			x2_y2,
			sizeof(x2_y2),
			NULL,
			0,
			md)))
		{
			error_code = COMPUTE_SM2_KDF_FAIL;
			goto clean_up;
		}

		/* If each component of t is zero, the random number k
		   should be re-generated. */
		flag = 1;
		for (i = 0; i < message_len; i++)
		{
			if (t[i] != 0)
			{
				flag = 0;
				break;
			}
		}
	} while (flag);

	if (!(EC_POINT_get_affine_coordinates_GFp(group,
		c1_pt,
		bn_c1_x,
		bn_c1_y,
		ctx)))
	{
		goto clean_up;
	}

	if (BN_bn2binpad(bn_c1_x,
		c1_x,
		sizeof(c1_x)) != sizeof(c1_x))
	{
		goto clean_up;
	}
	if (BN_bn2binpad(bn_c1_y,
		c1_y,
		sizeof(c1_y)) != sizeof(c1_y))
	{
		goto clean_up;
	}
	c1_point[0] = 0x4;
	memcpy((c1_point + 1), c1_x, sizeof(c1_x));
	memcpy((c1_point + 1 + sizeof(c1_x)), c1_y, sizeof(c1_y));
	memcpy(c1, c1_point, sizeof(c1_point));

	EVP_DigestInit_ex(md_ctx, md, NULL);
	EVP_DigestUpdate(md_ctx, x2, sizeof(x2));
	EVP_DigestUpdate(md_ctx, message, message_len);
	EVP_DigestUpdate(md_ctx, y2, sizeof(y2));
	EVP_DigestFinal_ex(md_ctx, c3, NULL);

	for (i = 0; i < message_len; i++)
	{
		c2[i] = message[i] ^ t[i];
	}
	error_code = 0;

clean_up:
	if (t)
	{
		free(t);
	}
	if (ctx)
	{
		BN_CTX_end(ctx);
		BN_CTX_free(ctx);
	}
	if (group)
	{
		EC_GROUP_free(group);
	}

	if (pub_key_pt)
	{
		EC_POINT_free(pub_key_pt);
	}
	if (c1_pt)
	{
		EC_POINT_free(c1_pt);
	}
	if (s_pt)
	{
		EC_POINT_free(s_pt);
	}
	if (ec_pt)
	{
		EC_POINT_free(ec_pt);
	}
	if (md_ctx)
	{
		EVP_MD_CTX_free(md_ctx);
	}

	return error_code;
}

std::string Utility::getOpenSSLError()
{
	BIO *bio = BIO_new(BIO_s_mem());
	ERR_print_errors(bio);
	char *buf;
	size_t len = BIO_get_mem_data(bio, &buf);
	std::string ret(buf, len);
	BIO_free(bio);
	return ret;
}