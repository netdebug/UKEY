

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for C:\Users\ADMINI~1\AppData\Local\Temp\IDL5E5F.tmp:
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


#ifndef __iWebAssist_h__
#define __iWebAssist_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DiWebAssist_FWD_DEFINED__
#define ___DiWebAssist_FWD_DEFINED__
typedef interface _DiWebAssist _DiWebAssist;

#endif 	/* ___DiWebAssist_FWD_DEFINED__ */


#ifndef ___DiWebAssistEvents_FWD_DEFINED__
#define ___DiWebAssistEvents_FWD_DEFINED__
typedef interface _DiWebAssistEvents _DiWebAssistEvents;

#endif 	/* ___DiWebAssistEvents_FWD_DEFINED__ */


#ifndef __iWebAssist_FWD_DEFINED__
#define __iWebAssist_FWD_DEFINED__

#ifdef __cplusplus
typedef class iWebAssist iWebAssist;
#else
typedef struct iWebAssist iWebAssist;
#endif /* __cplusplus */

#endif 	/* __iWebAssist_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __iWebAssistLib_LIBRARY_DEFINED__
#define __iWebAssistLib_LIBRARY_DEFINED__

/* library iWebAssistLib */
/* [custom][custom][custom][helpcontext][helpfile][helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_iWebAssistLib;

#ifndef ___DiWebAssist_DISPINTERFACE_DEFINED__
#define ___DiWebAssist_DISPINTERFACE_DEFINED__

/* dispinterface _DiWebAssist */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DiWebAssist;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4240FB41-A213-42B6-8CB5-E6705C99B319")
    _DiWebAssist : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DiWebAssistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DiWebAssist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DiWebAssist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DiWebAssist * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DiWebAssist * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DiWebAssist * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DiWebAssist * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DiWebAssist * This,
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
    } _DiWebAssistVtbl;

    interface _DiWebAssist
    {
        CONST_VTBL struct _DiWebAssistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DiWebAssist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DiWebAssist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DiWebAssist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DiWebAssist_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DiWebAssist_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DiWebAssist_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DiWebAssist_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DiWebAssist_DISPINTERFACE_DEFINED__ */


#ifndef ___DiWebAssistEvents_DISPINTERFACE_DEFINED__
#define ___DiWebAssistEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DiWebAssistEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DiWebAssistEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1108D978-446E-46DC-AE89-0A9282119578")
    _DiWebAssistEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DiWebAssistEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DiWebAssistEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DiWebAssistEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DiWebAssistEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DiWebAssistEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DiWebAssistEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DiWebAssistEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DiWebAssistEvents * This,
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
    } _DiWebAssistEventsVtbl;

    interface _DiWebAssistEvents
    {
        CONST_VTBL struct _DiWebAssistEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DiWebAssistEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DiWebAssistEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DiWebAssistEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DiWebAssistEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DiWebAssistEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DiWebAssistEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DiWebAssistEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DiWebAssistEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_iWebAssist;

#ifdef __cplusplus

class DECLSPEC_UUID("E99768C0-3DE2-4C53-AA41-188550CA66AC")
iWebAssist;
#endif
#endif /* __iWebAssistLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


