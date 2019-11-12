#include "WindowsGBKEncoding.h"
#include "Poco/String.h"

namespace Poco {


	const char* WindowsGBKEncoding::_names[] =
	{
		"windows-GBK",
		"Windows-GBK",
		NULL
	};


	const TextEncoding::CharacterMap WindowsGBKEncoding::_charMap =
	{
		/*          00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f   */
		/* 00 */	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		/* 10 */	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
		/* 20 */	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
		/* 30 */	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
		/* 40 */	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
		/* 50 */	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
		/* 60 */	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
		/* 70 */	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
		/* 80 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* 90 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* a0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* b0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* c0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* d0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* e0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		/* f0 */	-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
	};


	WindowsGBKEncoding::WindowsGBKEncoding()
	{
	}


	WindowsGBKEncoding::~WindowsGBKEncoding()
	{
	}


	const char* WindowsGBKEncoding::canonicalName() const
	{
		return _names[0];
	}


	bool WindowsGBKEncoding::isA(const std::string& encodingName) const
	{
		for (const char** name = _names; *name; ++name)
		{
			if (Poco::icompare(encodingName, *name) == 0)
				return true;
		}
		return false;
	}


	const TextEncoding::CharacterMap& WindowsGBKEncoding::characterMap() const
	{
		return _charMap;
	}


	int WindowsGBKEncoding::convert(const unsigned char* bytes) const
	{
		return _charMap[*bytes];
	}


	int WindowsGBKEncoding::convert(int ch, unsigned char* bytes, int length) const
	{
		unsigned short word;
		unsigned short gbk_word;
		unsigned char *gbk_ptr = (unsigned char *)bytes;
		int *uni_ptr = &ch;
		unsigned int uni_ind = 0, gbk_ind = 0, gbk_num = 0;
		int word_pos;

		if (!bytes)
			return 0;

		word = *(uni_ptr + uni_ind);
		uni_ind++;

		/*if (word == 0x0000)  //字符串结束符
			return 0;*/

		if (word <= 0x80)
		{
			*(gbk_ptr + gbk_ind) = (unsigned char)word;
			gbk_ind++;
			gbk_num += 1;//gbk字符+1
		}
		else
		{
			if (length < 2)
			{
				return 0;
			}
			word_pos = word - unicode_first_code;
			if (word >= unicode_first_code && word <= unicode_last_code && word_pos < gbk_buf_size)
			{
				gbk_word = gbkTables[word_pos];//gbk_word是gbk编码，但是为unsigned short类型，需要拆分成两个字节

				*(gbk_ptr + gbk_ind) = (unsigned char)(gbk_word >> 8);//提取高8位
				gbk_ind++;
				*(gbk_ptr + gbk_ind) = (unsigned char)(gbk_word >> 0);//提取低8位
				gbk_ind++;
				gbk_num += 2;//gbk字符加2个
			}
			else
			{
				//没找到编码。
				/*中日韩符号和标点符号
					CJK Symbols and Punctuation
					U+3000 - U+303F*/
					/*中文标点的Unicode编码
						0b7	·	183
						00d7	×	215
						2014	—	8212
						2018	‘	8216
						2019	’	8217
						201c	“	8220
						201d	”	8221
						2026	…	8230
						3001	、	12289
						3002	。	12290
						300a	《	12298
						300b	》	12299
						300e	『	12302
						300f	』	12303
						3010	【	12304
						3011	】	12305
						ff01	!	65281
						ff08	（	65288
						ff09	）	65289
						ff0c	，	65292
						ff1a	：	65306
						ff1b	；	65307
						ff1f	？	65311*/

				unsigned int UBiaodianT[23] =
				{
					183,
					215,
					8212,
					8216,
					8217,
					8220,
					8221,
					8230,
					12289,
					12290,
					12298,
					12299,
					12302,
					12303,
					12304,
					12305,
					65281,
					65288,
					65289,
					65292,
					65306,
					65307,
					65311
				};
				/*gbk中文标点符号表
					·A1A4
					×A1C1
					—A1AA
					‘A1AE
					’A1AF
					“A1B0
					”A1B1
					…A1AD
					、A1A2
					。A1A3
					《A1B6
					》A1B7
					『A1BA
					』A1BB
					【A1BE
					】A1BF
					!21
					（A3A8
					）A3A9
					，A3AC
					：A3BA
					；A3BB
					？A3BF
					*/
				unsigned int GBiaodianT[23] =
				{
					0xA1A4,
					0xA1C1,
					0xA1AA,
					0xA1AE,
					0xA1AF,
					0xA1B0,
					0xA1B1,
					0xA1AD,
					0xA1A2,
					0xA1A3,
					0xA1B6,
					0xA1B7,
					0xA1BA,
					0xA1BB,
					0xA1BE,
					0xA1BF,
					0x21,
					0xA3A8,
					0xA3A9,
					0xA3AC,
					0xA3BA,
					0xA3BB,
					0xA3BF
				};

				int i = 0;
				for (i = 0; i <= 23; i++)
				{
					if (word == UBiaodianT[i])
					{
						break;
					}
				}
				if (i >= 24)
				{
					return 1;//找不到字符
				}
				else
				{
					unsigned int temp = GBiaodianT[i];
					*(gbk_ptr + gbk_ind) = (unsigned char)(temp >> 8);//提取高8位
					gbk_ind++;
					*(gbk_ptr + gbk_ind) = (unsigned char)(temp >> 0);//提取低8位
					gbk_ind++;
					gbk_num += 2;//gbk字符加2个
				}
			}
		}


		return gbk_num;
	}


	int WindowsGBKEncoding::queryConvert(const unsigned char* bytes, int length) const
	{
		unsigned short word;
		unsigned char *gbk_ptr = (unsigned char *)bytes;
		UINT16 result = 0;
		unsigned short *uni_ptr = &result;
		unsigned int uni_ind = 0, gbk_ind = 0, uni_num = 0;
		unsigned char ch;
		int word_pos;

		if (!bytes)
			return 0;


		ch = *(gbk_ptr + gbk_ind);

		/*if (ch == 0x00)
			return 0;*/

		if (ch > 0x80)
		{
			if (length < 2)
			{
				return -2;
			}
			//将gbk编码的中文字符的两个字节组合成一个    unsigned short word;
			word = *(gbk_ptr + gbk_ind);
			word <<= 8;
			word += *(gbk_ptr + gbk_ind + 1);
			gbk_ind += 2;

			word_pos = word - gbk_first_code;
			if (word >= gbk_first_code && word <= gbk_last_code && (word_pos < unicode_buf_size))
			{
				*(uni_ptr + uni_ind) = unicodeTables[word_pos];
				uni_ind++;
				uni_num++;
			}
		}
		else
		{
			gbk_ind++;
			*(uni_ptr + uni_ind) = ch;
			uni_ind++;
			uni_num++;
		}





		return result;
	}


	int WindowsGBKEncoding::sequenceLength(const unsigned char* bytes, int length) const
	{

		if (*bytes > 0x80)
		{
			return 2;
		}
		else if (*bytes >= 0)
		{
			return 1;
		}
		else {
			return -1;
		}


	}


} // namespace Poco

