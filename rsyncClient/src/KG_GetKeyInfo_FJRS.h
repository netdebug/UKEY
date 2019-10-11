

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __KG_GetKeyInfo_FJRS_h__
#define __KG_GetKeyInfo_FJRS_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DKG_GetKeyInfo_FJRS_FWD_DEFINED__
#define ___DKG_GetKeyInfo_FJRS_FWD_DEFINED__
typedef interface _DKG_GetKeyInfo_FJRS _DKG_GetKeyInfo_FJRS;

#endif 	/* ___DKG_GetKeyInfo_FJRS_FWD_DEFINED__ */


#ifndef ___DKG_GetKeyInfo_FJRSEvents_FWD_DEFINED__
#define ___DKG_GetKeyInfo_FJRSEvents_FWD_DEFINED__
typedef interface _DKG_GetKeyInfo_FJRSEvents _DKG_GetKeyInfo_FJRSEvents;

#endif 	/* ___DKG_GetKeyInfo_FJRSEvents_FWD_DEFINED__ */


#ifndef __KG_GetKeyInfo_FJRS_FWD_DEFINED__
#define __KG_GetKeyInfo_FJRS_FWD_DEFINED__

#ifdef __cplusplus
typedef class KG_GetKeyInfo_FJRS KG_GetKeyInfo_FJRS;
#else
typedef struct KG_GetKeyInfo_FJRS KG_GetKeyInfo_FJRS;
#endif /* __cplusplus */

#endif 	/* __KG_GetKeyInfo_FJRS_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __KG_GetKeyInfo_FJRSLib_LIBRARY_DEFINED__
#define __KG_GetKeyInfo_FJRSLib_LIBRARY_DEFINED__

/* library KG_GetKeyInfo_FJRSLib */
/* [custom][custom][custom][version][uuid] */ 




EXTERN_C const IID LIBID_KG_GetKeyInfo_FJRSLib;

#ifndef ___DKG_GetKeyInfo_FJRS_DISPINTERFACE_DEFINED__
#define ___DKG_GetKeyInfo_FJRS_DISPINTERFACE_DEFINED__

/* dispinterface _DKG_GetKeyInfo_FJRS */
/* [uuid] */ 


EXTERN_C const IID DIID__DKG_GetKeyInfo_FJRS;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B31B9B8B-A16F-4C8F-A547-0227FBC98A74")
    _DKG_GetKeyInfo_FJRS : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DKG_GetKeyInfo_FJRSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DKG_GetKeyInfo_FJRS * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DKG_GetKeyInfo_FJRS * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DKG_GetKeyInfo_FJRS * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DKG_GetKeyInfo_FJRS * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DKG_GetKeyInfo_FJRS * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DKG_GetKeyInfo_FJRS * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DKG_GetKeyInfo_FJRS * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DKG_GetKeyInfo_FJRSVtbl;

    interface _DKG_GetKeyInfo_FJRS
    {
        CONST_VTBL struct _DKG_GetKeyInfo_FJRSVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DKG_GetKeyInfo_FJRS_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DKG_GetKeyInfo_FJRS_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DKG_GetKeyInfo_FJRS_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DKG_GetKeyInfo_FJRS_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DKG_GetKeyInfo_FJRS_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DKG_GetKeyInfo_FJRS_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DKG_GetKeyInfo_FJRS_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DKG_GetKeyInfo_FJRS_DISPINTERFACE_DEFINED__ */


#ifndef ___DKG_GetKeyInfo_FJRSEvents_DISPINTERFACE_DEFINED__
#define ___DKG_GetKeyInfo_FJRSEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DKG_GetKeyInfo_FJRSEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DKG_GetKeyInfo_FJRSEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F91B8D9A-898D-4999-88A5-A25208B927A3")
    _DKG_GetKeyInfo_FJRSEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DKG_GetKeyInfo_FJRSEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DKG_GetKeyInfo_FJRSEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DKG_GetKeyInfo_FJRSEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DKG_GetKeyInfo_FJRSEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DKG_GetKeyInfo_FJRSEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DKG_GetKeyInfo_FJRSEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DKG_GetKeyInfo_FJRSEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DKG_GetKeyInfo_FJRSEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DKG_GetKeyInfo_FJRSEventsVtbl;

    interface _DKG_GetKeyInfo_FJRSEvents
    {
        CONST_VTBL struct _DKG_GetKeyInfo_FJRSEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DKG_GetKeyInfo_FJRSEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DKG_GetKeyInfo_FJRSEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DKG_GetKeyInfo_FJRSEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DKG_GetKeyInfo_FJRSEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DKG_GetKeyInfo_FJRSEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DKG_GetKeyInfo_FJRSEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DKG_GetKeyInfo_FJRSEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DKG_GetKeyInfo_FJRSEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_KG_GetKeyInfo_FJRS;

#ifdef __cplusplus

class DECLSPEC_UUID("CE70417E-B247-43B3-A089-8273FAD99F1B")
KG_GetKeyInfo_FJRS;
#endif
#endif /* __KG_GetKeyInfo_FJRSLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


