#pragma once
#include <string>
struct IKG_HARD_EXT;
namespace Reach {

	class BridgeKG_HARD_EXT
	{
	public:
		BridgeKG_HARD_EXT();
		~BridgeKG_HARD_EXT();

		void WebConnectDev();
		void WebDisconnectDev();

		void WebGetKeyDefineInfo();
		const std::string WebGetSerial();

	private:
		void release();
		IKG_HARD_EXT* _ext;
	};
}