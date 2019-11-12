#pragma once
#include "Poco/Foundation.h"
#include "Poco/TextEncoding.h"
#include"gbkTables.h"
#include"unicodeTables.h"

namespace Poco {


	class /*Foundation_API*/ WindowsGBKEncoding : public TextEncoding
		/// Windows Codepage 1252 text encoding.
	{
	public:
		WindowsGBKEncoding();
		~WindowsGBKEncoding();
		const char* canonicalName() const;
		bool isA(const std::string& encodingName) const;
		const CharacterMap& characterMap() const;
		int convert(const unsigned char* bytes) const;
		int convert(int ch, unsigned char* bytes, int length) const;
		int queryConvert(const unsigned char* bytes, int length) const;
		int sequenceLength(const unsigned char* bytes, int length) const;
		
	private:
		static const char* _names[];
		static const CharacterMap _charMap;
	};


} // namespace Poco
