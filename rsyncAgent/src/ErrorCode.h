#pragma once

#define RAR_OK									0x0000	///�ɹ�
#define RAR_NODEVICE							0x9001	///δ��⵽UKEY֤��
#define RAR_MULTIPLEDEVICE						0x9002	///��⵽���UKEY֤��
#define RAR_NOUNIQUEID							0x9003	///δ���յ�Ψһ��ʶ
#define RAR_UNIQUEIDUNCORRECT					0x9004	///Ψһ��ʶ�뵱ǰUKEY֤�鲻��
#define RAR_NOBASE64CERT						0x9005	///δ���յ�֤��base64����
#define RAR_ERRORBASE64							0x9006	///���յ���֤��base64���������޷�����
#define RAR_ERRORINFOOID						0x9007	///��ȡ��������Ϣ��ʶ�����
#define RAR_OPENDEVICEFAILED					0x9008	///�򿪵�ǰUKEY֤��ʧ��
#define RAR_9009								0x9009	///��ǰUKEY֤�鲻��Ҫ��ȡΨһ��ʶ
#define RAR_9010								0x9010	///δ���յ�֤�����
#define RAR_9011								0x9011	///�������
#define RAR_ERRORCERTTYPE						0x9012	///֤�����Ͳ�������
#define RAR_9013								0x9013	///��ǰUKEY֤��������֤֤�����
#define RAR_9014								0x9014	///��ǰUKEY֤����δ��������������͵�֤��
#define RAR_9015								0x9015	///δ���յ���Ϣ��ʶ
#define RAR_9016								0x9016	///���յ�����Ϣ��ʶ����δ�ڶ������
#define RAR_9017								0x9017	///���յ���֤�����޸���Ϣ��ʶ��
#define RAR_9018								0x9018	///��UKEY֤��ʧ��
#define RAR_9019								0x9019	///��ǰUKEY֤���в������û���ʶ
#define RAR_9020								0x9020	///δ���յ���Ȩ��
#define RAR_9021								0x9021	///���յ�����Ȩ�����
#define RAR_9022								0x9022	///ͨѶ�쳣
#define RAR_ERRNOENCRYPT						0x9023	///δ���յ�����������
#define RAR_ERRENCRYPTBASE64CERT				0x9024	///���յ���֤��base64���������޷����ڼ���
#define RAR_9025								0x9025	///���յ��Ĵ��������ĳ������ܿ�֧�ֳ���
#define RAR_ERRNODECRYPT						0x9026	///δ���յ������ܵ�����
#define RAR_ERRDECRYPTFILEFORMAT				0x9027	///�����ܵ����ĸ�ʽ�����޷�����
#define RAR_9028								0x9028	///δ��֤UKEY֤�����
#define RAR_ERRDECRYPTCERT						0x9029	///�����ܵ����ķǵ�ǰUKEY֤����ܣ��޷�����
#define RAR_ENCYPTFAILED						0x9030	///����ʧ��
#define RAR_DECRYPTFAILED						0x9031	///����ʧ��
#define RAR_UNKNOWNERR							0x9999	///δ֪����