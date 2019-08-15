#pragma once

struct IIDBHOCtrl;

namespace Reach {
	class BridgeWindowsLiveLogin
	{
	public:
		BridgeWindowsLiveLogin();
		~BridgeWindowsLiveLogin();

		void GetAuthenticatedUserToken();
	private:
		IIDBHOCtrl* _bho;
	};
}