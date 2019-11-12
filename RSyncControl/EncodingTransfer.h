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
	DWORD nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节  
	UCHAR chr;
	BOOL bAllAscii = TRUE; //如果全部都是ASCII, 说明不是UTF-8  
	for (int i = 0; i < length; ++i)
	{
		chr = *(str + i);
		if ((chr & 0x80) != 0) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx  
			bAllAscii = FALSE;
		if (nBytes == 0) //如果不是ASCII码,应该是多字节符,计算字节数  
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
		else //多字节符的非首字节,应为 10xxxxxx  
		{
			if ((chr & 0xC0) != 0x80)
				return FALSE;

			nBytes--;
		}
	}
	if (nBytes > 0) //违返规则  
		return FALSE;
	if (bAllAscii) //如果全部都是ASCII, 说明不是UTF-8  
		return FALSE;

	return TRUE;
}
BSTR EncodingTransfer(BSTR str)
{
	std::wstring destinateBuffer;
	std::string ss;
	ss = _com_util::ConvertBSTRToString(str);
	//MessageBoxA(0, ss.c_str(), "编码转换前", 1);
	if (IsTextUTF8((char*)(ss.c_str()), ss.length()))
	{
		Poco::UnicodeConverter::convert(ss, destinateBuffer);
	}
	else
	{
		destinateBuffer = s2ws(ss);
	}
	
	//MessageBox(0, destinateBuffer.c_str(),L"编码转换结果",1);
	return _bstr_t(destinateBuffer.data());

}