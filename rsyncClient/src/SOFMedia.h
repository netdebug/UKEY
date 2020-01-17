#pragma once
#include "MediaBase.h"

namespace Reach {

	class SOFMedia
		: public MediaBase
	{
		/// 
		/// VID_22FB&PID_1014&REV_0101	ZTXA			008	USK218_GM.dll
		/// VID_055C&PID_E618&REV_0100	LongMai			009	mtoken_gm3000.dll
		/// VID_1D99&PID_0001&REV_0101	XS				001	SKF_APP_XS.dll
		/// VID_0096&PID_0309&REV_3200	FT 3000GM		011	SNCA_3000GM.dll
		/// VID_1EA8&PID_C001&REV_0100	WDC				007	NetcaSKF.dll
		/// VID_5488&PID_0004&REV_0300	HT				002	SKFAPI20079.dll 
		///	Same as HT									005	SKFAPI20549.dll
		/// VID_6588&PID_1514&REV_0000	LinGuo			003	lgu3073_p1514_gm.dll
		/// VID_096E&PID_0703&REV_7103	FT epass3003	010	ePass3K3GM_for_guocai.dll
		///												012 gdca_dal_szd3003_sm2.dll
		///												004 gm3k_for_bjca.dll
		///												006 FJCAMedia
	public:
		SOFMedia(const std::string& hid);
		~SOFMedia();
		virtual void open();
		virtual void extract();
		virtual void close();
		void GetCertBase64String();
		void FetchKeySN();
		void GetContainerId();
		void KeySN();
		void handleLastError(const std::string & result);

	private:
		std::string _uid;
		std::string _hid;
		const std::string _signType = "1";
	};
}