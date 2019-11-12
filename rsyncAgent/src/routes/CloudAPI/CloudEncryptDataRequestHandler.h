#pragma once

#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/DynamicStruct.h"
#include "Poco/JSON/Object.h"
#include "Poco/FileStream.h"
//#include "Poco/Crypto/CipherFactory.h"
//#include "Poco/Crypto/CipherKey.h"
//#include "Poco/Crypto/Cipher.h"
//#include "Poco/Crypto/ECKey.h"
//#include "Poco/Crypto/CryptoStream.h"
//#include "Poco/Crypto/ECDSADigestEngine.h"
#include "Poco/HexBinaryEncoder.h"
#include "Poco/HexBinaryDecoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "../Command.h"
#include "../RESTfulRequestHandler.h"
#include "CloudCommand.h"
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/crypto.h>

namespace Reach {

	using Poco::Util::Application;
	using Poco::URI;
	using Poco::JSON::Parser;
	using Poco::JSON::Object;
	using Poco::DynamicStruct;
	using Poco::FileInputStream;
	using Poco::HexBinaryEncoder;
	using Poco::HexBinaryDecoder;

	///RS_CloudEncryptData
	class CloudEncryptData : public Command, public CloudCommand
	{
	public:
		CloudEncryptData(const std::string& symKey, const std::string& transid, const std::string& token, const std::string& url) :
			CloudCommand(url),
			_symKey(symKey),
			_transid(transid),
			_token(token),
			_action("")
		{
			g_pubkey = ""
				"-----BEGIN PUBLIC KEY-----\r\n"
				"MFkwEwYHKoZIzj0CAQYIKoEcz1UBgi0DQgAEPCU4B2kPThX/gOk+dCAm6opsi5VZ\r\n"
				"UadwGvIWe10HWOm8pTZRpv+Akb6HhJpnyITTMvnFWQ36ebVSexU7KJSZtA==\r\n"
				"-----END PUBLIC KEY-----\r\n"
				"";

			g_prikey = ""
				"-----BEGIN EC PRIVATE KEY-----\r\n"
				"Proc-Type: 4,ENCRYPTED\r\n"
				"DEK-Info: SMS4-CBC,A9B7D7B184D261B5F157B7A5173C0498\r\n"
				"\r\n"
				"llSyh1hIYx2956hVEzZvYSbApSQXOHGl3KS/+vwq9WxDZi+eWgIMu5f9pXcKJLV2\r\n"
				"5tw1etHVhVsvVskZ1ZYJ5RjdjX9Kvqw7YAWSdWduB72lWSvW9PUgNhliTRoqbe44\r\n"
				"i0j5E1iJRaUd+c9eGE6l6kswOBTjI0bZ9FTMg6bqjZ8=\r\n"
				"-----END EC PRIVATE KEY-----\r\n"
				"";
			g_fjprikey = ""
				"ASN1 OID: sm2p256v1\r\n"
				"NIST CURVE: SM2\r\n"
				"-----BEGIN EC PARAMETERS-----\r\n"
				"BggqgRzPVQGCLQ==\r\n"
				"-----END EC PARAMETERS-----\r\n"
				"-----BEGIN EC PRIVATE KEY-----\r\n"
				"MHcCAQEEIK2E4tOTtBhl5e8aD08bJBIwpV5POeyBqgQSjo3bKFByoAoGCCqBHM9V\r\n"
				"AYItoUQDQgAE/816jFNfcn7lfLfUUkhp3PWu1R7BhGobujB+856XKVRVlBPrLU2L\r\n"
				"AlZBUs/HEGkAAGcE4j4yxnfrE6gKCYeJbQ==\r\n"
				"-----END EC PRIVATE KEY-----\r\n"
				"";
			privateKeyPassphrase = "Fjreach";
		}
		void run()
		{
#ifdef TEST
			std::string source(_symKey);
			v_encrypt_by_sm2(std::string("standard encryption"), "0420F19FF762F0CC0EE77243FF76E02657E6596A4F9CD74A671BA862A485441051ED415A59DA78D5D087AFCB2EF12DF99561FB658B11645D3F92C4CA638730BA05");
			add("encSymKey", ciphertext);
			add("signCertBase64", "signCertBase64");
			add("encCertBase64", "encCertBase64");
#else
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			std::string source(_symKey);
			std::string pubkey(extract("body", "pubkey"));
			v_encrypt_by_sm2(source, pubkey);

			add("encSymKey", ciphertext);
			add("signCertBase64", extract("body", "signCertBase64"));
			add("encCertBase64", extract("body", "encCertBase64"));
#endif // TEST	
		}
	protected:
		void v_encrypt_by_sm2(const std::string& plaintext, const std::string& pubkey)
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
			ciphertext = Poco::toUpper(ostr.str());
		}
		int sm2_encrypt(const unsigned char *message, const int message_len, const unsigned char *pub_key, unsigned char *c1, unsigned char *c3, unsigned char *c2)
		{
			//������Կ�Դ������
#define CREATE_SM2_KEY_PAIR_FAIL     0x1002
#define ALLOCATION_MEMORY_FAIL       0x1004
//�ӽ��ܴ������
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

		virtual void mixValue()
		{
			Application& app = Application::instance();
			FileInputStream in(app.config().getString("cloudconfigdir", "") + "CloudEncryptData.json");
			DynamicStruct ds = *parse(in).extract<Object::Ptr>();
			ds["bodyJson"]["token"] = _token;
			ds["bodyJson"]["transid"] = _transid;

			ds["bodyJson"]["authCode"] = app.config().getString("authCode", "");
			ds["body"] = ds["bodyJson"].toString();
			ds.erase("bodyJson");

			prepare(ds.toString());
			poco_information_f1(app.logger(), "CloudEncryptData mixValue:\n%s", ds.toString());
		}
		std::string getOpenSSLError()
		{
			BIO *bio = BIO_new(BIO_s_mem());
			ERR_print_errors(bio);
			char *buf;
			size_t len = BIO_get_mem_data(bio, &buf);
			std::string ret(buf, len);
			BIO_free(bio);
			return ret;
		}

	private:
		std::string _symKey;
		std::string _transid;
		std::string _token;
		std::string _action;
		std::string _msg;

		std::string ciphertext;
		std::string g_pubkey;
		std::string g_prikey;
		std::string privateKeyPassphrase;
		std::string g_fjprikey;
	};

	class CloudEncryptDataRequestHandler : public RESTfulRequestHandler
	{
	public:
		void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
		{
			Application& app = Application::instance();
			poco_information_f1(app.logger(), "Request from %s", request.clientAddress().toString());
			RESTfulRequestHandler::handleCORS(request, response);

			HTMLForm form(request, request.stream());
			std::string symKey = form.get("symKey", "");
			std::string transid = form.get("transid", "");
			std::string token = form.get("token", "");
			std::string url = app.config().getString("rsigncloudTest");
			CloudEncryptData command(symKey, transid, token, url);
			command.execute();

			return response.sendBuffer(command().data(), command().length());
		}
	};
}