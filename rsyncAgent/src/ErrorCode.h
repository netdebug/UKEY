#pragma once

#define RAR_OK									0x0000	///成功
#define RAR_NODEVICE							0x9001	///未检测到UKEY证书
#define RAR_MULTIPLEDEVICE						0x9002	///检测到多个UKEY证书
#define RAR_NOUNIQUEID							0x9003	///未接收到唯一标识
#define RAR_UNIQUEIDUNCORRECT					0x9004	///唯一标识与当前UKEY证书不符
#define RAR_NOBASE64CERT						0x9005	///未接收到证书base64编码
#define RAR_ERRORBASE64							0x9006	///接收到的证书base64编码有误，无法解析
#define RAR_ERRORINFOOID						0x9007	///获取、解析信息标识项错误
#define RAR_OPENDEVICEFAILED					0x9008	///打开当前UKEY证书失败
#define RAR_9009								0x9009	///当前UKEY证书不需要获取唯一标识
#define RAR_9010								0x9010	///未接收到证书口令
#define RAR_9011								0x9011	///密码错误
#define RAR_ERRORCERTTYPE						0x9012	///证书类型参数错误
#define RAR_9013								0x9013	///当前UKEY证书需先验证证书口令
#define RAR_9014								0x9014	///当前UKEY证书中未包含传入参数类型的证书
#define RAR_9015								0x9015	///未接收到信息标识
#define RAR_9016								0x9016	///接收到的信息标识错误，未在定义表中
#define RAR_9017								0x9017	///接收到的证书中无该信息标识项
#define RAR_9018								0x9018	///打开UKEY证书失败
#define RAR_9019								0x9019	///当前UKEY证书中不包含用户标识
#define RAR_9020								0x9020	///未接收到授权码
#define RAR_9021								0x9021	///接收到的授权码错误
#define RAR_9022								0x9022	///通讯异常
#define RAR_ERRNOENCRYPT						0x9023	///未接收到待加密明文
#define RAR_ERRENCRYPTBASE64CERT				0x9024	///接收到的证书base64编码有误，无法用于加密
#define RAR_9025								0x9025	///接收到的待加密明文超出加密可支持长度
#define RAR_ERRNODECRYPT						0x9026	///未接收到待解密的密文
#define RAR_ERRDECRYPTFILEFORMAT				0x9027	///待解密的密文格式错误，无法解密
#define RAR_9028								0x9028	///未验证UKEY证书口令
#define RAR_ERRDECRYPTCERT						0x9029	///待解密的密文非当前UKEY证书加密，无法解密
#define RAR_ENCYPTFAILED						0x9030	///加密失败
#define RAR_DECRYPTFAILED						0x9031	///解密失败
#define RAR_UNKNOWNERR							0x9999	///未知错误