#pragma once

#include <string>

struct IPDFReader;
namespace Reach {

	class BridgePDFReader
	{
	public:
		BridgePDFReader();
		~BridgePDFReader();

		void set(const std::string& name, const std::string& value);

	private:
		void release();

		IPDFReader*	_reader;
	};
}