//GmEsealProvider

#ifndef _GMESEALPROVIDER_H_
#define _GMESEALPROVIDER_H_

#ifdef GMESEALPROVIDER_EXPORTS
#define GMESEALPROVIDER_API __declspec(dllexport)
#else
#define GMESEALPROVIDER_API __declspec(dllimport)
#endif	//END GMESEALPROVIDER_EXPORTS

#ifndef STD_CALL
#define STD_CALL __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif

	GMESEALPROVIDER_API int STD_CALL IsUKIn();
	GMESEALPROVIDER_API int STD_CALL GetSealCount();
	GMESEALPROVIDER_API char* STD_CALL ReadSealData(int nIndex);
	GMESEALPROVIDER_API int STD_CALL FreePCharPointer(char* pchPointer);
	
#ifdef __cplusplus
}
#endif

#endif	//END _GMESEALPROVIDER_H_