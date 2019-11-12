#pragma once
#include "Poco/TextConverter.h"
#include "Poco/ASCIIEncoding.h"
#include "Poco/Latin1Encoding.h"
#include "Poco/Latin2Encoding.h"
#include "Poco/Latin9Encoding.h"
#include "Poco/Windows1250Encoding.h"
#include "Poco/Windows1251Encoding.h"
#include "Poco/Windows1252Encoding.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/Unicode.h"
#include "Poco/UnicodeConverter.h"
#include "Poco/UTF16Encoding.h"
#include "Poco/UTF32Encoding.h"

#include <fstream>
#include <stdio.h>
//#include "WindowsGBKEncoding.h"
#include <sstream>
#include <string>
#include <comutil.h>

static BSTR EncodingTransfer(BSTR str);

static std::string ws2s(const std::wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	std::string result = pchar;
	return result;
}

static std::wstring s2ws(const std::string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	std::wstring result = pwchar;
	return result;
}

static BOOL IsTextUTF8(char* str, ULONGLONG length)
{
	DWORD nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�  
	UCHAR chr;
	BOOL bAllAscii = TRUE; //���ȫ������ASCII, ˵������UTF-8  
	for (int i = 0; i < length; ++i)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // �ж��Ƿ�ASCII����,�������,˵���п�����UTF-8,ASCII��7λ����,����һ���ֽڴ�,���λ���Ϊ0,o0xxxxxxx  
			bAllAscii = FALSE;
		if (nBytes == 0) //�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���  
		{
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
					nBytes = 6;
				else if (chr >= 0xF8)
					nBytes = 5;
				else if (chr >= 0xF0)
					nBytes = 4;
				else if (chr >= 0xE0)
					nBytes = 3;
				else if (chr >= 0xC0)
					nBytes = 2;
				else
					return FALSE;

				nBytes--;
			}
		}
		else //���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx  
		{
			if ((chr & 0xC0) != 0x80)
				return FALSE;

			nBytes--;
		}
	}
	if (nBytes > 0) //Υ������  
		return FALSE;
	if (bAllAscii) //���ȫ������ASCII, ˵������UTF-8  
		return FALSE;

	return TRUE;
}
BSTR EncodingTransfer(BSTR str)
{
	std::wstring destinateBuffer;
	std::string ss;
	ss = _com_util::ConvertBSTRToString(str);
	//MessageBoxA(0, ss.c_str(), "����ת��ǰ", 1);
	if (IsTextUTF8((char*)(ss.c_str()), ss.length()))
	{
		Poco::UnicodeConverter::convert(ss, destinateBuffer);
	}
	else
	{
		destinateBuffer = s2ws(ss);
	}
	
	//MessageBox(0, destinateBuffer.c_str(),L"����ת�����",1);
	return _bstr_t(destinateBuffer.data());

}