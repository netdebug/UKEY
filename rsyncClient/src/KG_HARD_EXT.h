

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for KG_HARD_EXT.IDL:
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


#ifndef __KG_HARD_EXT_h__
#define __KG_HARD_EXT_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IKG_HARD_EXT_FWD_DEFINED__
#define __IKG_HARD_EXT_FWD_DEFINED__
typedef interface IKG_HARD_EXT IKG_HARD_EXT;

#endif 	/* __IKG_HARD_EXT_FWD_DEFINED__ */


#ifndef __KG_HARD_EXT_FWD_DEFINED__
#define __KG_HARD_EXT_FWD_DEFINED__

#ifdef __cplusplus
typedef class KG_HARD_EXT KG_HARD_EXT;
#else
typedef struct KG_HARD_EXT KG_HARD_EXT;
#endif /* __cplusplus */

#endif 	/* __KG_HARD_EXT_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __KG_HARD_EXT_V9Lib_LIBRARY_DEFINED__
#define __KG_HARD_EXT_V9Lib_LIBRARY_DEFINED__

/* library KG_HARD_EXT_V9Lib */
/* [custom][custom][custom][version][uuid] */ 



EXTERN_C const IID LIBID_KG_HARD_EXT_V9Lib;

#ifndef __IKG_HARD_EXT_INTERFACE_DEFINED__
#define __IKG_HARD_EXT_INTERFACE_DEFINED__

/* interface IKG_HARD_EXT */
/* [object][oleautomation][nonextensible][dual][uuid] */ 


EXTERN_C const IID IID_IKG_HARD_EXT;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("02CA4235-81DF-4ABF-8395-FE054000BA20")
    IKG_HARD_EXT : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebConnectDev( 
            long nUsbPort,
            /* [retval][out] */ long *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebDisconnectDev( 
            /* [retval][out] */ long *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebVerifyUserPin( 
            BSTR szUserPin,
            /* [retval][out] */ long *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebGetSerial( 
            /* [retval][out] */ BSTR *ret) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebGetKeyDefineInfo( 
            long nUsbPort,
            /* [retval][out] */ BSTR *szFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebReadFile( 
            long lIndexFile,
            long lIsBase64,
            /* [retval][out] */ BSTR *strData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebWriteFile( 
            long lIndexFile,
            long lIsBase64,
            BSTR strData,
            /* [retval][out] */ long *lRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebDeleteFile( 
            long lIndexFile,
            /* [retval][out] */ long *lRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WebGetStyle( 
            /* [retval][out] */ long *ret) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetKeyCertInfo( 
            /* [retval][out] */ BSTR *strCertInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSetParam( 
            /* [in] */ BSTR strParam,
            BSTR ParamValue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebResetPin( 
            /* [in] */ BSTR szOPin,
            /* [in] */ BSTR szUserPin,
            /* [retval][out] */ long *ret) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IKG_HARD_EXTVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKG_HARD_EXT * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKG_HARD_EXT * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKG_HARD_EXT * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IKG_HARD_EXT * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IKG_HARD_EXT * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IKG_HARD_EXT * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IKG_HARD_EXT * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebConnectDev )( 
            IKG_HARD_EXT * This,
            long nUsbPort,
            /* [retval][out] */ long *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebDisconnectDev )( 
            IKG_HARD_EXT * This,
            /* [retval][out] */ long *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebVerifyUserPin )( 
            IKG_HARD_EXT * This,
            BSTR szUserPin,
            /* [retval][out] */ long *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebGetSerial )( 
            IKG_HARD_EXT * This,
            /* [retval][out] */ BSTR *ret);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebGetKeyDefineInfo )( 
            IKG_HARD_EXT * This,
            long nUsbPort,
            /* [retval][out] */ BSTR *szFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebReadFile )( 
            IKG_HARD_EXT * This,
            long lIndexFile,
            long lIsBase64,
            /* [retval][out] */ BSTR *strData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebWriteFile )( 
            IKG_HARD_EXT * This,
            long lIndexFile,
            long lIsBase64,
            BSTR strData,
            /* [retval][out] */ long *lRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebDeleteFile )( 
            IKG_HARD_EXT * This,
            long lIndexFile,
            /* [retval][out] */ long *lRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WebGetStyle )( 
            IKG_HARD_EXT * This,
            /* [retval][out] */ long *ret);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetKeyCertInfo )( 
            IKG_HARD_EXT * This,
            /* [retval][out] */ BSTR *strCertInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSetParam )( 
            IKG_HARD_EXT * This,
            /* [in] */ BSTR strParam,
            BSTR ParamValue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebResetPin )( 
            IKG_HARD_EXT * This,
            /* [in] */ BSTR szOPin,
            /* [in] */ BSTR szUserPin,
            /* [retval][out] */ long *ret);
        
        END_INTERFACE
    } IKG_HARD_EXTVtbl;

    interface IKG_HARD_EXT
    {
        CONST_VTBL struct IKG_HARD_EXTVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKG_HARD_EXT_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IKG_HARD_EXT_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IKG_HARD_EXT_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IKG_HARD_EXT_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IKG_HARD_EXT_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IKG_HARD_EXT_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IKG_HARD_EXT_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IKG_HARD_EXT_WebConnectDev(This,nUsbPort,ret)	\
    ( (This)->lpVtbl -> WebConnectDev(This,nUsbPort,ret) ) 

#define IKG_HARD_EXT_WebDisconnectDev(This,ret)	\
    ( (This)->lpVtbl -> WebDisconnectDev(This,ret) ) 

#define IKG_HARD_EXT_WebVerifyUserPin(This,szUserPin,ret)	\
    ( (This)->lpVtbl -> WebVerifyUserPin(This,szUserPin,ret) ) 

#define IKG_HARD_EXT_WebGetSerial(This,ret)	\
    ( (This)->lpVtbl -> WebGetSerial(This,ret) ) 

#define IKG_HARD_EXT_WebGetKeyDefineInfo(This,nUsbPort,szFileID)	\
    ( (This)->lpVtbl -> WebGetKeyDefineInfo(This,nUsbPort,szFileID) ) 

#define IKG_HARD_EXT_WebReadFile(This,lIndexFile,lIsBase64,strData)	\
    ( (This)->lpVtbl -> WebReadFile(This,lIndexFile,lIsBase64,strData) ) 

#define IKG_HARD_EXT_WebWriteFile(This,lIndexFile,lIsBase64,strData,lRet)	\
    ( (This)->lpVtbl -> WebWriteFile(This,lIndexFile,lIsBase64,strData,lRet) ) 

#define IKG_HARD_EXT_WebDeleteFile(This,lIndexFile,lRet)	\
    ( (This)->lpVtbl -> WebDeleteFile(This,lIndexFile,lRet) ) 

#define IKG_HARD_EXT_WebGetStyle(This,ret)	\
    ( (This)->lpVtbl -> WebGetStyle(This,ret) ) 

#define IKG_HARD_EXT_WebGetKeyCertInfo(This,strCertInfo)	\
    ( (This)->lpVtbl -> WebGetKeyCertInfo(This,strCertInfo) ) 

#define IKG_HARD_EXT_WebSetParam(This,strParam,ParamValue)	\
    ( (This)->lpVtbl -> WebSetParam(This,strParam,ParamValue) ) 

#define IKG_HARD_EXT_WebResetPin(This,szOPin,szUserPin,ret)	\
    ( (This)->lpVtbl -> WebResetPin(This,szOPin,szUserPin,ret) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IKG_HARD_EXT_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_KG_HARD_EXT;

#ifdef __cplusplus

class DECLSPEC_UUID("7848343F-1875-4F22-9E0C-96BC8BF9796C")
KG_HARD_EXT;
#endif
#endif /* __KG_HARD_EXT_V9Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


