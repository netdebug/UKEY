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
	//using Poco::Crypto::CipherFactory;
	//using Poco::Crypto::Cipher;
	//using Poco::Crypto::CipherKey;
	//using Poco::Crypto::ECKey;
	//using Poco::Crypto::CryptoOutputStream;
	using Poco::HexBinaryEncoder;
	using Poco::HexBinaryDecoder;
	using Poco::Base64Encoder;
	using Poco::Base64Decoder;

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

#define TEST

#ifdef TEST
			/*std::string encyptdata = "8648CBA49F41C4BFC85A8C0773E432D52BBF7C90405C0F7B9514858616E4885EEE78E98103F79BA7E64461650ACD9444BDAE7FD58CDE5526CDFB02EFBD6F369BCA248303ED4AFC8BFF7D0419358BD888ED3C3069FAAE33D5A5FCEFC1777A0530D2901429684D8D6ECCF4A6F49BDB1F2D94ACF75EF2DC9090C6DC219D4AE78EC16FD9FA0C64564079";
			external_decrypt(encyptdata, g_prikey, privateKeyPassphrase);*/
			std::string source(_symKey);
			//v_encrypt_by_sm2(std::string("standard encryption"), "0420F19FF762F0CC0EE77243FF76E02657E6596A4F9CD74A671BA862A485441051ED415A59DA78D5D087AFCB2EF12DF99561FB658B11645D3F92C4CA638730BA05");
			v_encrypt_by_sm2(std::string("standard encryption"), "04F6E0C3345AE42B51E06BF50B98834988D54EBC7460FE135A48171BC0629EAE205EEDE253A530608178A98F1E19BB737302813BA39ED3FA3C51639D7A20C7391A");
			//external_encrypt(std::string("werwr的范德萨发我是阿道夫"), "0420F19FF762F0CC0EE77243FF76E02657E6596A4F9CD74A671BA862A485441051ED415A59DA78D5D087AFCB2EF12DF99561FB658B11645D3F92C4CA638730BA05");
			//external_decrypt(encyptdata, g_prikey, privateKeyPassphrase);

			/*std::string encdata = "fAAAAEAAAABWzv1g18h8AA1Y71f6c7pNnA36CMCKczFJ"
				"XC4do/K9UjG35+bMgYn2aFNc4Pjq8b1t6EwYL2yOcW94DTqXCiPDEAAAABRd/1"
				"Zr970cWqnQsBqM5XsgAAAAlwILWeyMyjGCI9IqbAK5AbXdVluBvAPFtTdCXfGa"
				"ATwgAAAAPA+FSdI3UkfgDaCRqK1PL21InJ7hdpOBMMhvQXJaWQQ=";
			external_decrypt_base64(encdata, g_fjprikey, privateKeyPassphrase);*/

			/*std::string prikey = "3690655E33D5EA3D9A4AE1A1ADD766FDEA045CDEAA43A9206FB8C430CEFE0D94";
			std::string encdata = "04A0D90BA78BE7BE415230ABC5709AF7FDF3263F758C311448755E315181E9282F0E6BD86040425DA95EB4F236A76E074BD7627DB47C86FB5A175AA8C66F32F96AAB63FF6909C32E7DCB940EE056B6537C59555435284E6CCB99C46EE5A808C1ED71A495FFEDE2BF136F87EED5";
			external_decrypt_base64(encdata, prikey, "");
			add("encSymKey", encyptdata);
			add("signCertBase64", "signCertBase64");
			add("encCertBase64", "encCertBase64");*/
#else
			mixValue();
			sendRequest();

			if (!success())
				throw CloudCommandException(extract("head", "message"),
					std::stoi(extract("head", "code"), 0, 16));

			std::string source(_symKey);
			std::string pubkey(extract("body", "pubkey"));
			external_encrypt(source, pubkey, true);

			add("encSymKey", encyptdata);
			add("signCertBase64", extract("body", "signCertBase64"));
			add("encCertBase64", extract("body", "encCertBase64"));
#endif // TEST	
		}
	protected:
		void v_encrypt_by_sm2(const std::string& source, const std::string& pubkey)
		{
			Application& app = Application::instance();

			std::istringstream istr(pubkey);
			std::string skey;
			HexBinaryDecoder decoder(istr);
			int c = decoder.get();
			while (c != -1) { skey += char(c); c = decoder.get(); }

			poco_information_f1(app.logger(), "%s", skey);

			unsigned char c1[65], c3[32];
			unsigned char *c2;
			if (!(c2 = (unsigned char *)malloc(source.size())))
				throw Poco::OutOfMemoryException();

			if (!sm2_encrypt((unsigned char*)source.data(), source.size(), (unsigned char*)skey.data(), c1, c3, c2))
			{
				std::ostringstream ostr;
				HexBinaryEncoder encoder(ostr);
				encoder.rdbuf()->setLineLength(0);
				encoder.write((const char*)c1, sizeof(c1));
				encoder.write((const char*)c3, sizeof(c3));
				encoder.write((const char*)c2, source.size());
				
				poco_information_f1(app.logger(), "%s", ostr.str());
			}
		}
		int sm2_encrypt(const unsigned char *message, const int message_len, const unsigned char *pub_key, unsigned char *c1, unsigned char *c3, unsigned char *c2)
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
		/*
		void external_encrypt(const std::string& source, const std::string& pubkey, bool hexdump)
		{
			std::string ec;
			std::string start("-----BEGIN PUBLIC KEY-----\r\n");
			std::string end("-----END PUBLIC KEY-----\r\n");
			std::string header("");
			std::string s;
			std::string pem;
			pem.append(header).append(pubkey);
			std::istringstream istr(pem);
			HexBinaryDecoder decoder(istr);
			int c = decoder.get();
			while (c != -1) { s += char(c); c = decoder.get(); }
			std::ostringstream base64;
			Base64Encoder encoder(base64);
			encoder.write(s.data(), s.length());
			encoder.close();

			external_encrypt(source, start + base64.str()+ "\r\n" + end);
		}

		void external_encrypt(const std::string& source, const char* pubkey)
		{
			Application& app = Application::instance();

			EC_KEY				*key = NULL;
			EC_POINT			*pub_key;
			const EC_GROUP		*group;
			

			key = EC_KEY_new_by_curve_name(NID_sm2p256v1);
			group = EC_KEY_get0_group(key);
			pub_key = EC_POINT_new(group);
			EC_POINT_hex2point(group, pubkey, pub_key, 0);
			EC_KEY_set_public_key(key, pub_key);

			if (!EC_KEY_check_key(key)) {
				printf("EC_KEY_check_key failed:\n");
				printf("%s\n", ERR_error_string(ERR_get_error(), NULL));
			}
			else {
				printf("Public key verified OK\n");
			}

			int ret = 0;
			size_t outlen = 512;
			std::vector<char> encrypt(outlen, 0);
			ret = SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), (unsigned char*)encrypt.data(), &outlen,
				key);

			if (!ret && encrypt.size() < outlen)
			{
				encrypt.resize(outlen, 0);
				ret = SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), (unsigned char*)encrypt.data(), &outlen,
					key);
			}

			if (!ret)
			{
				poco_information_f1(app.logger(), "%s", getOpenSSLError());
				throw Poco::Exception(getOpenSSLError());
			}

			{
				encrypt.resize(outlen);
				//std::reverse(encrypt.begin(), encrypt.end());
				std::ostringstream ostr;
				HexBinaryEncoder encoder(ostr);
				encoder.rdbuf()->setLineLength(0);
				encoder.write(encrypt.data(), outlen);
				encyptdata = ostr.str();
				poco_information_f2(app.logger(), "encryptSM2,\n %s \n len:%u", encyptdata, encyptdata.length());
			}
		}

		void external_encrypt(const std::string& source, const std::string& pubkey)
		{
			Application& app = Application::instance();

			std::istringstream iPub(pubkey);
			Poco::Crypto::ECKey ek(&iPub);

			ek.save("pubkeyself.pem");

			int ret = 0;
			size_t outlen = 512;
			std::vector<char> encrypt(outlen, 0);

			ret = SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), (unsigned char*)encrypt.data(), &outlen,
				ek.impl()->getECKey());

			if (!ret && encrypt.size() < outlen)
			{
				encrypt.resize(outlen, 0);
				ret = SM2_encrypt_with_recommended((unsigned char*)source.data(), source.size(), (unsigned char*)encrypt.data(), &outlen,
					ek.impl()->getECKey());
			}

			if (!ret)
			{
				poco_information_f1(app.logger(), "%s", getOpenSSLError());
				throw Poco::Exception(getOpenSSLError());
			}

			
			
			{
				encrypt.resize(outlen);
	
				std::ostringstream ostr;
				HexBinaryEncoder encoder(ostr);
				encoder.rdbuf()->setLineLength(0);
				encoder.write(encrypt.data(), outlen);
				encyptdata = ostr.str();
				poco_information_f2(app.logger(), "encryptSM2,\n %s \n len:%u", encyptdata, encyptdata.length());
			}
			
		}

		void external_decrypt_base64(const std::string& encrypt, const std::string& prikey, const std::string& privateKeyPassphrase)
		{
			Application& app = Application::instance();

			std::vector<char> enc;
			std::istringstream istr(encrypt);
			Base64Decoder decoder(istr);
			int c = decoder.get();
			while (c != -1) { enc.push_back(char(c)); c = decoder.get(); }

			int ret = 0;
			std::istringstream iPri(prikey);
			Poco::Crypto::ECKey ek(0, &iPri, privateKeyPassphrase);
			size_t outlen = 128;
			std::vector<char> decrypt(outlen, 0);
			//ret = SM2_decrypt_with_recommended((unsigned char*)enc.data(), enc.size(), (unsigned char*)decrypt.data(), &outlen,
			//	ek.impl()->getECKey());

			if (!ret && decrypt.size() < outlen) {

				decrypt.resize(outlen, 0);
			//	ret = SM2_decrypt_with_recommended((unsigned char*)enc.data(), enc.size(), (unsigned char*)decrypt.data(), &outlen,
			//		ek.impl()->getECKey());
			}

			if (!ret)
			{
				poco_information_f1(app.logger(), "%s", getOpenSSLError());
				throw Poco::Exception(getOpenSSLError());
			}

			std::string dec(decrypt.data(), decrypt.size());
			poco_information_f2(app.logger(), "decryptSM2,\n %s len:%u:", dec, dec.length());
		}

		void external_decrypt(const std::string& encrypt, const std::string& prikey, const std::string& privateKeyPassphrase)
		{
			Application& app = Application::instance();

			std::vector<char> enc;
			std::istringstream istr(encrypt);
			HexBinaryDecoder decoder(istr);
			int c = decoder.get();
			while (c != -1) { enc.push_back(char(c)); c = decoder.get(); }

			int ret = 0;
			std::istringstream iPri(prikey);
			Poco::Crypto::ECKey ek(0, &iPri, privateKeyPassphrase);
			size_t outlen = 128;
			std::vector<char> decrypt(outlen, 0);
			//ret = SM2_decrypt_with_recommended((unsigned char*)enc.data(), enc.size(), (unsigned char*)decrypt.data(), &outlen,
			//	ek.impl()->getECKey());
			
			if (!ret && decrypt.size() < outlen) {

				decrypt.resize(outlen, 0);
			//	ret = SM2_decrypt_with_recommended((unsigned char*)enc.data(), enc.size(), (unsigned char*)decrypt.data(), &outlen,
			//		ek.impl()->getECKey());
			}
			
			if (!ret)
			{
				poco_information_f1(app.logger(), "%s", getOpenSSLError());
				throw Poco::Exception(getOpenSSLError());
			}

			std::string dec(decrypt.data(), decrypt.size());
			poco_information_f2(app.logger(), "decryptSM2,\n %s len:%u:", dec, dec.length());
		}
		*/
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
	private:
		std::string _symKey;
		std::string _transid;
		std::string _token;
		std::string _action;
		std::string _msg;

		std::string encyptdata;
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