

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Nov 13 16:21:49 2019
 */
/* Compiler settings for RSyncControl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_RSyncControlLib,0x5FF751F0,0x5CAB,0x496C,0xA5,0xE7,0x1F,0x3B,0x2C,0xBD,0x2F,0x4E);


MIDL_DEFINE_GUID(IID, DIID__DRSyncControl,0x7A58AA86,0xD40D,0x4611,0x9D,0xA1,0xDF,0xCE,0xAE,0x95,0x31,0x5A);


MIDL_DEFINE_GUID(IID, DIID__DRSyncControlEvents,0xEECD3FF1,0xDED8,0x44B3,0x87,0x7C,0x99,0xD0,0x56,0xD5,0x44,0x9D);


MIDL_DEFINE_GUID(CLSID, CLSID_RSyncControl,0xF84C8F57,0x5A05,0x4D8C,0x82,0x6D,0x29,0x58,0x9C,0x7A,0x12,0x1C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



