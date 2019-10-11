

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for KG_GetKeyInfo_FJRS.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_KG_GetKeyInfo_FJRSLib,0x2A9EB1FF,0xCEF1,0x45FA,0xB4,0x5F,0x24,0xC1,0xD0,0x59,0xCE,0xCC);


MIDL_DEFINE_GUID(IID, DIID__DKG_GetKeyInfo_FJRS,0xB31B9B8B,0xA16F,0x4C8F,0xA5,0x47,0x02,0x27,0xFB,0xC9,0x8A,0x74);


MIDL_DEFINE_GUID(IID, DIID__DKG_GetKeyInfo_FJRSEvents,0xF91B8D9A,0x898D,0x4999,0x88,0xA5,0xA2,0x52,0x08,0xB9,0x27,0xA3);


MIDL_DEFINE_GUID(CLSID, CLSID_KG_GetKeyInfo_FJRS,0xCE70417E,0xB247,0x43B3,0xA0,0x89,0x82,0x73,0xFA,0xD9,0x9F,0x1B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



