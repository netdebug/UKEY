

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 12 17:22:12 2019
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __RSyncControlidl_h__
#define __RSyncControlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DRSyncControl_FWD_DEFINED__
#define ___DRSyncControl_FWD_DEFINED__
typedef interface _DRSyncControl _DRSyncControl;
#endif 	/* ___DRSyncControl_FWD_DEFINED__ */


#ifndef ___DRSyncControlEvents_FWD_DEFINED__
#define ___DRSyncControlEvents_FWD_DEFINED__
typedef interface _DRSyncControlEvents _DRSyncControlEvents;
#endif 	/* ___DRSyncControlEvents_FWD_DEFINED__ */


#ifndef __RSyncControl_FWD_DEFINED__
#define __RSyncControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class RSyncControl RSyncControl;
#else
typedef struct RSyncControl RSyncControl;
#endif /* __cplusplus */

#endif 	/* __RSyncControl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __RSyncControlLib_LIBRARY_DEFINED__
#define __RSyncControlLib_LIBRARY_DEFINED__

/* library RSyncControlLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_RSyncControlLib;

#ifndef ___DRSyncControl_DISPINTERFACE_DEFINED__
#define ___DRSyncControl_DISPINTERFACE_DEFINED__

/* dispinterface _DRSyncControl */
/* [uuid] */ 


EXTERN_C const IID DIID__DRSyncControl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7A58AA86-D40D-4611-9DA1-DFCEAE95315A")
    _DRSyncControl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DRSyncControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DRSyncControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DRSyncControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DRSyncControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DRSyncControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DRSyncControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DRSyncControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DRSyncControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DRSyncControlVtbl;

    interface _DRSyncControl
    {
        CONST_VTBL struct _DRSyncControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DRSyncControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DRSyncControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DRSyncControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DRSyncControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DRSyncControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DRSyncControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DRSyncControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DRSyncControl_DISPINTERFACE_DEFINED__ */


#ifndef ___DRSyncControlEvents_DISPINTERFACE_DEFINED__
#define ___DRSyncControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DRSyncControlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DRSyncControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EECD3FF1-DED8-44B3-877C-99D056D5449D")
    _DRSyncControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DRSyncControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DRSyncControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DRSyncControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DRSyncControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DRSyncControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DRSyncControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DRSyncControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DRSyncControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DRSyncControlEventsVtbl;

    interface _DRSyncControlEvents
    {
        CONST_VTBL struct _DRSyncControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DRSyncControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DRSyncControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DRSyncControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DRSyncControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DRSyncControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DRSyncControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DRSyncControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DRSyncControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_RSyncControl;

#ifdef __cplusplus

class DECLSPEC_UUID("F84C8F57-5A05-4D8C-826D-29589C7A121C")
RSyncControl;
#endif
#endif /* __RSyncControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


