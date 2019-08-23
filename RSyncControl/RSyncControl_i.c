

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Aug 23 17:40:01 2019
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

MIDL_DEFINE_GUID(IID, LIBID_RSyncControlLib,0xa8de96ca,0x374b,0x497d,0xaa,0x5f,0x3c,0x03,0x09,0xc8,0xa9,0xf0);


MIDL_DEFINE_GUID(IID, DIID__DRSyncControl,0xdb403885,0xf81d,0x41d2,0x80,0xd7,0x40,0x36,0x50,0x97,0xd6,0x0c);


MIDL_DEFINE_GUID(IID, DIID__DRSyncControlEvents,0xb1c93fb3,0x0485,0x4837,0x9a,0xaf,0xaf,0x8f,0x96,0xa2,0xc0,0xd2);


MIDL_DEFINE_GUID(CLSID, CLSID_RSyncControl,0xa0b23721,0x9350,0x4b4d,0xb5,0x81,0x65,0xad,0xd1,0xa7,0x7a,0x5e);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



