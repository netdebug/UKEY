

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for WindowsLiveLogin.IDL:
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


#ifndef __WindowsLiveLogin_h__
#define __WindowsLiveLogin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIDBHOCtrl_FWD_DEFINED__
#define __IIDBHOCtrl_FWD_DEFINED__
typedef interface IIDBHOCtrl IIDBHOCtrl;

#endif 	/* __IIDBHOCtrl_FWD_DEFINED__ */


#ifndef __IDBHOCtrl_FWD_DEFINED__
#define __IDBHOCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class IDBHOCtrl IDBHOCtrl;
#else
typedef struct IDBHOCtrl IDBHOCtrl;
#endif /* __cplusplus */

#endif 	/* __IDBHOCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __IDBHOLib_LIBRARY_DEFINED__
#define __IDBHOLib_LIBRARY_DEFINED__

/* library IDBHOLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_IDBHOLib;

#ifndef __IIDBHOCtrl_INTERFACE_DEFINED__
#define __IIDBHOCtrl_INTERFACE_DEFINED__

/* interface IIDBHOCtrl */
/* [object][oleautomation][nonextensible][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IIDBHOCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5823EF01-E0A4-4822-AEBB-0A5D4FA381CF")
    IIDBHOCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllAccounts( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthenticatedUserToken( 
            /* [retval][out] */ BSTR *pbstrAuthenticatedUserToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAccount( 
            /* [in] */ BSTR bstrAccountName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAccount( 
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ int iOption) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ComputerSetting( 
            /* [retval][out] */ int *pVal) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ComputerSetting( 
            /* [in] */ int pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserList( 
            /* [in] */ BSTR bstrForcePwdUser,
            /* [retval][out] */ BSTR *pbstrUserList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUserTile( 
            /* [in] */ BSTR bstrTS,
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disable( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteUserExtendedProperty( 
            /* [in] */ BSTR proptodelete,
            /* [in] */ BSTR propFilter,
            /* [in] */ BSTR filterValue,
            /* [in] */ VARIANT_BOOL fExtendedFilter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateCertToken( 
            /* [in] */ BSTR bstrMemberName,
            /* [in] */ BSTR bstrThumbprint,
            /* [in] */ int iLen,
            /* [in] */ BSTR bstrPIN,
            /* [retval][out] */ BSTR *pbstrOutPutCertToken) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserExtendedProperty( 
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserProperty( 
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveSSOCreds( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteSSOCreds( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitNotForBrowser( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateEIDs( 
            /* [in] */ BSTR bstrCSPs,
            /* [in] */ BSTR bstrThumbprints,
            /* [retval][out] */ BSTR *pbstrEID_JS_Define) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserListEx( 
            /* [in] */ BSTR bstrForcePwdUser,
            /* [retval][out] */ BSTR *pbstrUserList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAutoSSOUserName( 
            /* [in] */ unsigned long dwSSOGroup,
            /* [retval][out] */ BSTR *pbstrUserName) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *pbstrVersion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthenticatedUserName( 
            /* [retval][out] */ BSTR *pbstrAuthenticatedUserName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUserExtendedProperty( 
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [in] */ BSTR bstrPropValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWgaTicket( 
            /* [retval][out] */ BSTR *pbstrWgaTicket) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAuthBufferEx( 
            /* [in] */ BSTR userName,
            /* [in] */ BSTR password,
            /* [in] */ BSTR daToken,
            /* [in] */ BSTR daTokenExpiryTime,
            /* [in] */ BSTR daTokenCreationTime,
            /* [in] */ BSTR encodedSessionKey,
            /* [in] */ BSTR flowToken,
            /* [retval][out] */ BSTR *pAuthBuffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveDAToken( 
            /* [in] */ BSTR daToken,
            /* [in] */ BSTR daTokenExpiryTime,
            /* [in] */ BSTR daTokenCreationTime,
            /* [in] */ BSTR encodedSessionKey) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIDBHOCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIDBHOCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIDBHOCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIDBHOCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIDBHOCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIDBHOCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIDBHOCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIDBHOCtrl * This,
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
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllAccounts )( 
            IIDBHOCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAuthenticatedUserToken )( 
            IIDBHOCtrl * This,
            /* [retval][out] */ BSTR *pbstrAuthenticatedUserToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAccount )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrAccountName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAccount )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPassword,
            /* [in] */ int iOption);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ComputerSetting )( 
            IIDBHOCtrl * This,
            /* [retval][out] */ int *pVal);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ComputerSetting )( 
            IIDBHOCtrl * This,
            /* [in] */ int pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUserList )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrForcePwdUser,
            /* [retval][out] */ BSTR *pbstrUserList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUserTile )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrTS,
            /* [in] */ BSTR bstrUrl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disable )( 
            IIDBHOCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteUserExtendedProperty )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR proptodelete,
            /* [in] */ BSTR propFilter,
            /* [in] */ BSTR filterValue,
            /* [in] */ VARIANT_BOOL fExtendedFilter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GenerateCertToken )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrMemberName,
            /* [in] */ BSTR bstrThumbprint,
            /* [in] */ int iLen,
            /* [in] */ BSTR bstrPIN,
            /* [retval][out] */ BSTR *pbstrOutPutCertToken);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUserExtendedProperty )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUserProperty )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [retval][out] */ BSTR *pbstrPropValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveSSOCreds )( 
            IIDBHOCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteSSOCreds )( 
            IIDBHOCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitNotForBrowser )( 
            IIDBHOCtrl * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumerateEIDs )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrCSPs,
            /* [in] */ BSTR bstrThumbprints,
            /* [retval][out] */ BSTR *pbstrEID_JS_Define);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetUserListEx )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrForcePwdUser,
            /* [retval][out] */ BSTR *pbstrUserList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAutoSSOUserName )( 
            IIDBHOCtrl * This,
            /* [in] */ unsigned long dwSSOGroup,
            /* [retval][out] */ BSTR *pbstrUserName);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IIDBHOCtrl * This,
            /* [retval][out] */ BSTR *pbstrVersion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAuthenticatedUserName )( 
            IIDBHOCtrl * This,
            /* [retval][out] */ BSTR *pbstrAuthenticatedUserName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetUserExtendedProperty )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR bstrAccountName,
            /* [in] */ BSTR bstrPropName,
            /* [in] */ BSTR bstrPropValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWgaTicket )( 
            IIDBHOCtrl * This,
            /* [retval][out] */ BSTR *pbstrWgaTicket);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAuthBufferEx )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR userName,
            /* [in] */ BSTR password,
            /* [in] */ BSTR daToken,
            /* [in] */ BSTR daTokenExpiryTime,
            /* [in] */ BSTR daTokenCreationTime,
            /* [in] */ BSTR encodedSessionKey,
            /* [in] */ BSTR flowToken,
            /* [retval][out] */ BSTR *pAuthBuffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveDAToken )( 
            IIDBHOCtrl * This,
            /* [in] */ BSTR daToken,
            /* [in] */ BSTR daTokenExpiryTime,
            /* [in] */ BSTR daTokenCreationTime,
            /* [in] */ BSTR encodedSessionKey);
        
        END_INTERFACE
    } IIDBHOCtrlVtbl;

    interface IIDBHOCtrl
    {
        CONST_VTBL struct IIDBHOCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIDBHOCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIDBHOCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIDBHOCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIDBHOCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIDBHOCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIDBHOCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIDBHOCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIDBHOCtrl_DeleteAllAccounts(This)	\
    ( (This)->lpVtbl -> DeleteAllAccounts(This) ) 

#define IIDBHOCtrl_GetAuthenticatedUserToken(This,pbstrAuthenticatedUserToken)	\
    ( (This)->lpVtbl -> GetAuthenticatedUserToken(This,pbstrAuthenticatedUserToken) ) 

#define IIDBHOCtrl_DeleteAccount(This,bstrAccountName)	\
    ( (This)->lpVtbl -> DeleteAccount(This,bstrAccountName) ) 

#define IIDBHOCtrl_AddAccount(This,bstrAccountName,bstrPassword,iOption)	\
    ( (This)->lpVtbl -> AddAccount(This,bstrAccountName,bstrPassword,iOption) ) 

#define IIDBHOCtrl_get_ComputerSetting(This,pVal)	\
    ( (This)->lpVtbl -> get_ComputerSetting(This,pVal) ) 

#define IIDBHOCtrl_put_ComputerSetting(This,pVal)	\
    ( (This)->lpVtbl -> put_ComputerSetting(This,pVal) ) 

#define IIDBHOCtrl_GetUserList(This,bstrForcePwdUser,pbstrUserList)	\
    ( (This)->lpVtbl -> GetUserList(This,bstrForcePwdUser,pbstrUserList) ) 

#define IIDBHOCtrl_SetUserTile(This,bstrTS,bstrUrl)	\
    ( (This)->lpVtbl -> SetUserTile(This,bstrTS,bstrUrl) ) 

#define IIDBHOCtrl_Disable(This)	\
    ( (This)->lpVtbl -> Disable(This) ) 

#define IIDBHOCtrl_DeleteUserExtendedProperty(This,proptodelete,propFilter,filterValue,fExtendedFilter)	\
    ( (This)->lpVtbl -> DeleteUserExtendedProperty(This,proptodelete,propFilter,filterValue,fExtendedFilter) ) 

#define IIDBHOCtrl_GenerateCertToken(This,bstrMemberName,bstrThumbprint,iLen,bstrPIN,pbstrOutPutCertToken)	\
    ( (This)->lpVtbl -> GenerateCertToken(This,bstrMemberName,bstrThumbprint,iLen,bstrPIN,pbstrOutPutCertToken) ) 

#define IIDBHOCtrl_GetUserExtendedProperty(This,bstrAccountName,bstrPropName,pbstrPropValue)	\
    ( (This)->lpVtbl -> GetUserExtendedProperty(This,bstrAccountName,bstrPropName,pbstrPropValue) ) 

#define IIDBHOCtrl_GetUserProperty(This,bstrAccountName,bstrPropName,pbstrPropValue)	\
    ( (This)->lpVtbl -> GetUserProperty(This,bstrAccountName,bstrPropName,pbstrPropValue) ) 

#define IIDBHOCtrl_SaveSSOCreds(This)	\
    ( (This)->lpVtbl -> SaveSSOCreds(This) ) 

#define IIDBHOCtrl_DeleteSSOCreds(This)	\
    ( (This)->lpVtbl -> DeleteSSOCreds(This) ) 

#define IIDBHOCtrl_InitNotForBrowser(This)	\
    ( (This)->lpVtbl -> InitNotForBrowser(This) ) 

#define IIDBHOCtrl_EnumerateEIDs(This,bstrCSPs,bstrThumbprints,pbstrEID_JS_Define)	\
    ( (This)->lpVtbl -> EnumerateEIDs(This,bstrCSPs,bstrThumbprints,pbstrEID_JS_Define) ) 

#define IIDBHOCtrl_GetUserListEx(This,bstrForcePwdUser,pbstrUserList)	\
    ( (This)->lpVtbl -> GetUserListEx(This,bstrForcePwdUser,pbstrUserList) ) 

#define IIDBHOCtrl_GetAutoSSOUserName(This,dwSSOGroup,pbstrUserName)	\
    ( (This)->lpVtbl -> GetAutoSSOUserName(This,dwSSOGroup,pbstrUserName) ) 

#define IIDBHOCtrl_get_Version(This,pbstrVersion)	\
    ( (This)->lpVtbl -> get_Version(This,pbstrVersion) ) 

#define IIDBHOCtrl_GetAuthenticatedUserName(This,pbstrAuthenticatedUserName)	\
    ( (This)->lpVtbl -> GetAuthenticatedUserName(This,pbstrAuthenticatedUserName) ) 

#define IIDBHOCtrl_SetUserExtendedProperty(This,bstrAccountName,bstrPropName,bstrPropValue)	\
    ( (This)->lpVtbl -> SetUserExtendedProperty(This,bstrAccountName,bstrPropName,bstrPropValue) ) 

#define IIDBHOCtrl_GetWgaTicket(This,pbstrWgaTicket)	\
    ( (This)->lpVtbl -> GetWgaTicket(This,pbstrWgaTicket) ) 

#define IIDBHOCtrl_GetAuthBufferEx(This,userName,password,daToken,daTokenExpiryTime,daTokenCreationTime,encodedSessionKey,flowToken,pAuthBuffer)	\
    ( (This)->lpVtbl -> GetAuthBufferEx(This,userName,password,daToken,daTokenExpiryTime,daTokenCreationTime,encodedSessionKey,flowToken,pAuthBuffer) ) 

#define IIDBHOCtrl_SaveDAToken(This,daToken,daTokenExpiryTime,daTokenCreationTime,encodedSessionKey)	\
    ( (This)->lpVtbl -> SaveDAToken(This,daToken,daTokenExpiryTime,daTokenCreationTime,encodedSessionKey) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIDBHOCtrl_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_IDBHOCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("D2517915-48CE-4286-970F-921E881B8C5C")
IDBHOCtrl;
#endif
#endif /* __IDBHOLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


