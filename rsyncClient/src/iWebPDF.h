

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for iWebPDF.IDL:
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


#ifndef __iWebPDF_h__
#define __iWebPDF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPDFReader_FWD_DEFINED__
#define __IPDFReader_FWD_DEFINED__
typedef interface IPDFReader IPDFReader;

#endif 	/* __IPDFReader_FWD_DEFINED__ */


#ifndef __IPDFReaderEvents_FWD_DEFINED__
#define __IPDFReaderEvents_FWD_DEFINED__
typedef interface IPDFReaderEvents IPDFReaderEvents;

#endif 	/* __IPDFReaderEvents_FWD_DEFINED__ */


#ifndef __PDFReader_FWD_DEFINED__
#define __PDFReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDFReader PDFReader;
#else
typedef struct PDFReader PDFReader;
#endif /* __cplusplus */

#endif 	/* __PDFReader_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __iWebPDF_LIBRARY_DEFINED__
#define __iWebPDF_LIBRARY_DEFINED__

/* library iWebPDF */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_iWebPDF;

#ifndef __IPDFReader_INTERFACE_DEFINED__
#define __IPDFReader_INTERFACE_DEFINED__

/* interface IPDFReader */
/* [object][oleautomation][dual][helpstring][version][uuid] */ 


EXTERN_C const IID IID_IPDFReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B23CD27-8626-47EC-AE24-E52909086E2B")
    IPDFReader : public IDispatch
    {
    public:
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ long Value) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AboutBox( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_WebUrl( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_WebUrl( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RecordID( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RecordID( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowTools( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowTools( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ExtParam( 
            /* [in] */ BSTR rhs) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SaveRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SaveRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PrintRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_PrintRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayMode( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayMode( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Zoom( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Zoom( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Rotate( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Rotate( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PageCount( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CurPage( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CurPage( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AlterUser( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AlterUser( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_LocalFileName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_MaxFileSize( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_MaxFileSize( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenUrlFile( 
            /* [in] */ BSTR sWebUrl,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebDownLoadFile( 
            /* [in] */ BSTR sWebUrl,
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoFirstPage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoLastPage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoPreviousPage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoNextPage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpen( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSave( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebClose( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveLocal( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenLocal( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveLocalDialog( 
            /* [retval][out] */ BSTR *sResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenLocalDialog( 
            /* [retval][out] */ BSTR *sResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveLocalFile( 
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenLocalFile( 
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSetMsgByName( 
            /* [in] */ BSTR sFieldName,
            /* [in] */ BSTR sFieldValue,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetMsgByName( 
            /* [in] */ BSTR sFieldName,
            /* [retval][out] */ BSTR *sResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebClearMessage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSendMessage( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebPrint( 
            /* [in] */ long Copies,
            /* [in] */ BSTR PrintName,
            /* [defaultvalue][in] */ long FromPage,
            /* [defaultvalue][in] */ long ToPage,
            /* [defaultvalue][in] */ VARIANT_BOOL ShowDlg,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnableTools( 
            /* [in] */ BSTR sTools,
            /* [in] */ long bEnable,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowMarks( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowMarks( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowMenus( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowMenus( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowState( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowState( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowSides( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowSides( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignature( 
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ long PageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowSignDlg( 
            /* [defaultvalue][in] */ long type,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowCheckDlg( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowParamDlg( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SignatureNames( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SignatureItem( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SignatureCount( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CertificateSign( 
            /* [in] */ long Index,
            /* [defaultvalue][in] */ BSTR CardPin,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteSignature( 
            /* [in] */ BSTR Password,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetErrorString( 
            /* [in] */ long Code,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE VerifyPin( 
            /* [in] */ BSTR CardPin,
            /* [retval][out] */ VARIANT_BOOL *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPageSize( 
            /* [in] */ long PageNo,
            /* [in] */ long Index,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetKeyCount( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WateMark( 
            /* [in] */ long StartPage,
            /* [in] */ long EndPage,
            /* [in] */ BSTR Text,
            /* [in] */ long nstrok,
            /* [in] */ long fontSize,
            /* [in] */ long Rotate,
            /* [in] */ VARIANT_BOOL Back,
            /* [defaultvalue][in] */ long X,
            /* [defaultvalue][in] */ long Y,
            /* [retval][out] */ VARIANT_BOOL *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PrintStatus( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SaveStatus( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EditStatus( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CopyStatus( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowSigns( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowSigns( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SideWidth( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SideWidth( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnablePages( 
            /* [in] */ BSTR Pages,
            /* [in] */ long Enable,
            /* [in] */ BSTR Text,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FileType( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FileType( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_isOpen( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShedCryptoDocument( 
            /* [defaultvalue][in] */ long IsSaveAs,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowTitle( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowTitle( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SideColor( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SideColor( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveSignData( 
            /* [retval][out] */ long *res) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadSignData( 
            /* [retval][out] */ long *res) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoBookMark( 
            /* [in] */ BSTR BookMark,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPublicParam( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [in] */ BSTR HeaderValue,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSignatureParam( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [in] */ BSTR HeaderValue,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ContentText( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PrnScreen( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_PrnScreen( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AppendMenu( 
            /* [in] */ BSTR Index,
            /* [in] */ BSTR Caption) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AppendTools( 
            /* [in] */ BSTR Index,
            /* [in] */ BSTR Caption,
            /* [in] */ long Icon) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FullSize( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SmallSize( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Language( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Language( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_VersionEx( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HaveSignature( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EvevtTeam( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_EvevtTeam( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MoveSignature( 
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CursorState( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CursorState( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindFirst( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FindNext( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnableUserTools( 
            /* [in] */ BSTR Index,
            /* [in] */ long Enabled) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnableUserMenus( 
            /* [in] */ BSTR Index,
            /* [in] */ long Enabled) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CopyRight( 
            /* [in] */ BSTR rhs) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Binary( 
            /* [retval][out] */ VARIANT *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Binary( 
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportPages( 
            /* [in] */ BSTR FileName,
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [in] */ long Place,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeletePages( 
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SearchText( 
            /* [in] */ BSTR Text,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ExtParam1( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ExtParam1( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ExtParam2( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ExtParam2( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ThirdTime( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ThirdTime( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureFileName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureFileName( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GrayDocument( 
            /* [in] */ BSTR ExParam,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportFieldValue( 
            /* [in] */ BSTR FieldName,
            /* [in] */ BSTR FieldValue,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ExportFieldValue( 
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportImagePage( 
            /* [in] */ BSTR FileName,
            /* [in] */ long Zoom,
            /* [in] */ long isMapping,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportTemplate( 
            /* [in] */ BSTR XML,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveAccessory( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FullScreen( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FullScreen( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoPreviousScreen( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoNextScreen( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GotoViewSignature( 
            /* [in] */ long Index,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CancelSignature( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveLocalFileEx( 
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR Ext1,
            /* [in] */ BSTR Ext2,
            /* [in] */ BSTR Ext3,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenLocalFileEx( 
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR Ext1,
            /* [in] */ BSTR Ext2,
            /* [in] */ BSTR Ext3,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetMAC( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetIP( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE HandWriter( 
            /* [in] */ long type,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EnableHandWriter( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_EnableHandWriter( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImage( 
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR Image,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertText( 
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR Text,
            /* [in] */ long fontSize,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageByCursor( 
            /* [in] */ BSTR Image,
            /* [in] */ long isURL,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LockScreen( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnlockScreen( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCoordinate( 
            /* [in] */ BSTR Value,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCoordinate( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SeriesSignature( 
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ShowSearchDlg( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowSchedule( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowSchedule( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AllowSignName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AllowSignName( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteUserTools( 
            /* [in] */ BSTR Index) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteUserMenus( 
            /* [in] */ BSTR Index) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddComment( 
            /* [in] */ long PageNo,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ BSTR Text,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowPostil( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowPostil( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FastSignature( 
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AllowMoveAnnot( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AllowMoveAnnot( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebInsertImage( 
            /* [in] */ BSTR Value,
            /* [in] */ long PageNo,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ImportFieldValueByXML( 
            /* [in] */ BSTR sXML,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EnableUpdating( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_EnableUpdating( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSetScrollBarPos( 
            /* [in] */ long xPos,
            /* [in] */ long yPos,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetKeySN( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageByPosition( 
            /* [in] */ BSTR sName,
            /* [in] */ long mode,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR sImagePath,
            /* [in] */ long isURL,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebPrintEx( 
            /* [in] */ long Copies,
            /* [in] */ BSTR PrinterName,
            /* [in] */ BSTR PageArea,
            /* [in] */ VARIANT_BOOL ShowDlg,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTextPostilInfo( 
            /* [retval][out] */ BSTR *sResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_DocumentModified( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_TextCommentRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_TextCommentRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CheckPdfHasSignature( 
            /* [in] */ BSTR filePath,
            /* [retval][out] */ BSTR *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowPostilList( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowPostilList( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSelectState( 
            /* [in] */ long state,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebDoffSealToImage( 
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_LocalPrinterNameList( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_LocalPrinterDriverList( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebImageToPDF( 
            /* [in] */ BSTR sImagePath,
            /* [in] */ BSTR sPdfPath,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebPrintControl( 
            /* [in] */ BSTR PrinterName,
            /* [in] */ long MaxPrintCopies,
            /* [in] */ long PrintCopies,
            /* [in] */ BSTR PrintPage,
            /* [in] */ long ShowDlg,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureOutputFlags( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureOutputFlags( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnabledHideKeywords( 
            /* [in] */ long Ch,
            /* [in] */ VARIANT_BOOL Value,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AppendHideKeywords( 
            /* [in] */ BSTR Keywords) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveSignDataToLocal( 
            /* [retval][out] */ BSTR *lRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadLocalSignData( 
            /* [in] */ BSTR strSignData,
            /* [retval][out] */ long *lRet) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_UserID( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_UserID( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureMode( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureMode( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateBarcodeSignature( 
            /* [in] */ BSTR barcodeString,
            /* [in] */ long bShowDlg,
            /* [in] */ BSTR SignPass,
            /* [in] */ long lStartPage,
            /* [in] */ long lEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lRet) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowDigitalSignature( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowDigitalSignature( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AppendRevision( 
            /* [in] */ BSTR Revision) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearRevisions( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCurrentRevision( 
            /* [in] */ BSTR CustomData,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RevisionCount( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRevisionCustomData( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *sRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCryptPassword( 
            /* [in] */ BSTR pwd,
            /* [retval][out] */ VARIANT_BOOL *lRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddImageText( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ long fontSize,
            /* [in] */ long FontColor,
            /* [in] */ BSTR FontName,
            /* [in] */ BSTR Text) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearImageText( void) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ImageTextEnabled( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ImageTextEnabled( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebAddBookmark( 
            /* [in] */ BSTR strValue,
            /* [retval][out] */ VARIANT_BOOL *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebDelBookmark( 
            /* [in] */ BSTR strValue,
            /* [retval][out] */ VARIANT_BOOL *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebGetFilePath( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignatureByName( 
            /* [in] */ BSTR sealName,
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ BSTR Password,
            /* [in] */ long mode,
            /* [in] */ BSTR posText,
            /* [in] */ BSTR protectArea,
            /* [retval][out] */ long *lRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateRayCodeSignature( 
            /* [in] */ BSTR SignPass,
            /* [in] */ long PageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateQRCodeSignature( 
            /* [in] */ BSTR QRCodeString,
            /* [in] */ long bShowDlg,
            /* [in] */ BSTR SigPass,
            /* [in] */ long lStartPage,
            /* [in] */ long lEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AppCode( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_AppCode( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_IsPrintControl( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_IsPrintControl( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowToolBarHint( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowToolBarHint( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertMoveText( 
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ BSTR Pos,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ImageAnnotDelRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ImageAnnotDelRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ImageAnnotMoveRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ImageAnnotMoveRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignatureByImage( 
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertMoveTextExt( 
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Pos,
            /* [in] */ long PosType,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignatureFrom( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignatureFrom( 
            /* [in] */ long Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_UserRole( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_UserRole( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GoToTextComment( 
            /* [in] */ BSTR TextID,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FastSignatureByImage( 
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_IsShowInputBox( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_IsShowInputBox( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSpecificSignCount( 
            /* [in] */ BSTR Pages,
            /* [in] */ long SignType,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PrintConfig( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_PrintConfig( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_WaterMarkVisible( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_WaterMarkVisible( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignaturePages( 
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Pages,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GoToText( 
            /* [in] */ BSTR Text,
            /* [in] */ long Page,
            /* [in] */ VARIANT_BOOL Case,
            /* [in] */ VARIANT_BOOL UpDown,
            /* [in] */ VARIANT_BOOL Selected,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsPagesSigned( 
            /* [in] */ BSTR Pages,
            /* [in] */ long SignType,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OpenStream( 
            /* [in] */ VARIANT *AStream,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveStream( 
            /* [out] */ VARIANT *AStream,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetUserPassWord( 
            /* [in] */ BSTR Password,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_DBSignType( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_DBSignType( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageByCursorExt( 
            /* [in] */ BSTR Image,
            /* [in] */ long isURL,
            /* [in] */ long isTrans,
            /* [in] */ long actWidth,
            /* [in] */ long actHeight,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetDocumentID( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ServerURL( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ServerURL( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPublicInfo( 
            /* [in] */ long type,
            /* [in] */ BSTR Value,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPublicInfo( 
            /* [in] */ long type,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CUSTOMPARAMS( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CUSTOMPARAMS( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTextPosition( 
            /* [in] */ long PageNo,
            /* [in] */ BSTR Text,
            /* [in] */ VARIANT_BOOL Case,
            /* [in] */ long PType,
            /* [retval][out] */ BSTR *sInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetAnnotTextFile( 
            /* [retval][out] */ BSTR *sFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeletePagesExt( 
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetAnnotString( 
            /* [retval][out] */ BSTR *sInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddCommentExt( 
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR Text,
            /* [in] */ BSTR CTime,
            /* [in] */ BSTR MTime,
            /* [in] */ BSTR UName,
            /* [in] */ BSTR UId,
            /* [in] */ BSTR TId,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StartRect( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRectInfo( 
            /* [retval][out] */ BSTR *sInfo) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageByString( 
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR CTime,
            /* [in] */ BSTR MTime,
            /* [in] */ BSTR UName,
            /* [in] */ BSTR UId,
            /* [in] */ BSTR strPic,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR PId,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPostilPenColor( 
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPostilPenWidth( 
            /* [in] */ long pWidth,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CancelPostil( 
            /* [retval][out] */ VARIANT_BOOL *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DrawRect( 
            /* [in] */ long PageNo,
            /* [in] */ float X1,
            /* [in] */ float Y1,
            /* [in] */ float X2,
            /* [in] */ float Y2,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFieldNames( 
            /* [retval][out] */ BSTR *strNames) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetBookMarks( 
            /* [retval][out] */ BSTR *strBookMarks) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GoToAnnot( 
            /* [in] */ BSTR strID,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCPUID( 
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetHarDiskID( 
            /* [retval][out] */ BSTR *strResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_IsLocalPrint( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_IsLocalPrint( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageByPositionExt( 
            /* [in] */ BSTR strLocationInfo,
            /* [in] */ long mode,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR strImagePath,
            /* [in] */ long isURL,
            /* [in] */ float TranPre,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignatureByImageExt( 
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [in] */ long nStartPageNo,
            /* [in] */ long nEndPageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ float TranPre,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MakeDocOWP( 
            /* [in] */ BSTR OWP,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CommentWindow( 
            /* [in] */ int AllOpen,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateBarCodeImage( 
            /* [in] */ BSTR BarCode,
            /* [in] */ long StartPage,
            /* [in] */ long EndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Pos,
            /* [in] */ long nType,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FileSize( 
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SeriesSignatureExt( 
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [in] */ double ZoomPercent,
            /* [in] */ double rDegree,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveLocalFileNoSignature( 
            /* [in] */ BSTR FileName,
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InsertImageExt( 
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR Image,
            /* [in] */ VARIANT_BOOL Tback,
            /* [in] */ float dTran,
            /* [in] */ float Rotate,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTextPositionAll( 
            /* [in] */ BSTR strText,
            /* [in] */ BSTR strFileName,
            /* [retval][out] */ BSTR *strInf) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateSignatureByString( 
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ BSTR Pos,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [in] */ long mode,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AnnotCoordinate( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_TSServerUrl( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_TSServerUrl( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_TSUser( 
            /* [in] */ BSTR rhs) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_TSPwd( 
            /* [in] */ BSTR rhs) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignSerial( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SignSerialEnabled( 
            /* [retval][out] */ VARIANT_BOOL *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignSerialEnabled( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearImageSignSerial( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddImageSignSerial( 
            /* [in] */ long fontSize,
            /* [in] */ long FontColor,
            /* [in] */ BSTR FontName,
            /* [in] */ BSTR SignSerial) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DrawRectExt( 
            /* [in] */ long PageNo,
            /* [in] */ float X1,
            /* [in] */ float Y1,
            /* [in] */ float X2,
            /* [in] */ float Y2,
            /* [in] */ long ishighlight,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CommentTextMoveRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CommentTextMoveRight( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRealSignature( 
            /* [in] */ BSTR strParam,
            /* [retval][out] */ BSTR *strResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateStraddleSignature( 
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Position,
            /* [in] */ long isBialteral,
            /* [in] */ long EvenOrOdd,
            /* [in] */ BSTR strRate,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetFieldByName( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFieldByName( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ BSTR *strResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearFieldByName( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MergeRealSignature( 
            /* [in] */ BSTR strFileName,
            /* [in] */ BSTR strSignInfo,
            /* [retval][out] */ long *lResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveFileToBase64( 
            /* [in] */ long type,
            /* [retval][out] */ BSTR *strResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebOpenBase64( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebSaveBase64( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CustomPdfDocInfo( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CustomPdfDocInfo( 
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE WebFastSave( 
            /* [retval][out] */ long *bResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_BufSize( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_BufSize( 
            /* [in] */ long Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SignatureCountExt( 
            /* [in] */ BSTR strName,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSignIfo( 
            /* [in] */ long nSigIndex,
            /* [in] */ BSTR strName,
            /* [retval][out] */ BSTR *sResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSignaturePos( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *strResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE FastSeriesSignature( 
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [in] */ long ReferencePoint,
            /* [retval][out] */ long *Result) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_isCopyRight( 
            /* [retval][out] */ long *Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SelectedBookMarkName( 
            /* [retval][out] */ BSTR *Value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PrintWaterMark( 
            /* [in] */ BSTR strContent,
            /* [in] */ BSTR strName,
            /* [in] */ long nFSize,
            /* [in] */ long nFRColor,
            /* [in] */ long nFGColor,
            /* [in] */ long nFBColor,
            /* [in] */ long nFRotate,
            /* [retval][out] */ long *lResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPDFReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPDFReader * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPDFReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPDFReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPDFReader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPDFReader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPDFReader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPDFReader * This,
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
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AboutBox )( 
            IPDFReader * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_WebUrl )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_WebUrl )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_RecordID )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_RecordID )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_FileName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_FileName )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UserName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_UserName )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowTools )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowTools )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ExtParam )( 
            IPDFReader * This,
            /* [in] */ BSTR rhs);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SaveRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SaveRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PrintRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_PrintRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayMode )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DisplayMode )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Zoom )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Zoom )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Rotate )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Rotate )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PageCount )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CurPage )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CurPage )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AlterUser )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AlterUser )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_LocalFileName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MaxFileSize )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MaxFileSize )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenUrlFile )( 
            IPDFReader * This,
            /* [in] */ BSTR sWebUrl,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebDownLoadFile )( 
            IPDFReader * This,
            /* [in] */ BSTR sWebUrl,
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoFirstPage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoLastPage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoPreviousPage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoNextPage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpen )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSave )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebClose )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveLocal )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenLocal )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveLocalDialog )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenLocalDialog )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveLocalFile )( 
            IPDFReader * This,
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenLocalFile )( 
            IPDFReader * This,
            /* [in] */ BSTR sFileName,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSetMsgByName )( 
            IPDFReader * This,
            /* [in] */ BSTR sFieldName,
            /* [in] */ BSTR sFieldValue,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetMsgByName )( 
            IPDFReader * This,
            /* [in] */ BSTR sFieldName,
            /* [retval][out] */ BSTR *sResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebClearMessage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSendMessage )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebPrint )( 
            IPDFReader * This,
            /* [in] */ long Copies,
            /* [in] */ BSTR PrintName,
            /* [defaultvalue][in] */ long FromPage,
            /* [defaultvalue][in] */ long ToPage,
            /* [defaultvalue][in] */ VARIANT_BOOL ShowDlg,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnableTools )( 
            IPDFReader * This,
            /* [in] */ BSTR sTools,
            /* [in] */ long bEnable,
            /* [retval][out] */ long *bResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowMarks )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowMarks )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowMenus )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowMenus )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowState )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowState )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowSides )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowSides )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignature )( 
            IPDFReader * This,
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ long PageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowSignDlg )( 
            IPDFReader * This,
            /* [defaultvalue][in] */ long type,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowCheckDlg )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowParamDlg )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SignatureNames )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SignatureItem )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SignatureCount )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CertificateSign )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [defaultvalue][in] */ BSTR CardPin,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeleteSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR Password,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetErrorString )( 
            IPDFReader * This,
            /* [in] */ long Code,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *VerifyPin )( 
            IPDFReader * This,
            /* [in] */ BSTR CardPin,
            /* [retval][out] */ VARIANT_BOOL *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPageSize )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ long Index,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetKeyCount )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WateMark )( 
            IPDFReader * This,
            /* [in] */ long StartPage,
            /* [in] */ long EndPage,
            /* [in] */ BSTR Text,
            /* [in] */ long nstrok,
            /* [in] */ long fontSize,
            /* [in] */ long Rotate,
            /* [in] */ VARIANT_BOOL Back,
            /* [defaultvalue][in] */ long X,
            /* [defaultvalue][in] */ long Y,
            /* [retval][out] */ VARIANT_BOOL *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PrintStatus )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SaveStatus )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EditStatus )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CopyStatus )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowSigns )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowSigns )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SideWidth )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SideWidth )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnablePages )( 
            IPDFReader * This,
            /* [in] */ BSTR Pages,
            /* [in] */ long Enable,
            /* [in] */ BSTR Text,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_FileType )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_FileType )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isOpen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShedCryptoDocument )( 
            IPDFReader * This,
            /* [defaultvalue][in] */ long IsSaveAs,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowTitle )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowTitle )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SideColor )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SideColor )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveSignData )( 
            IPDFReader * This,
            /* [retval][out] */ long *res);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LoadSignData )( 
            IPDFReader * This,
            /* [retval][out] */ long *res);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoBookMark )( 
            IPDFReader * This,
            /* [in] */ BSTR BookMark,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPublicParam )( 
            IPDFReader * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [in] */ BSTR HeaderValue,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetSignatureParam )( 
            IPDFReader * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [in] */ BSTR HeaderValue,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ContentText )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PrnScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_PrnScreen )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AppendMenu )( 
            IPDFReader * This,
            /* [in] */ BSTR Index,
            /* [in] */ BSTR Caption);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AppendTools )( 
            IPDFReader * This,
            /* [in] */ BSTR Index,
            /* [in] */ BSTR Caption,
            /* [in] */ long Icon);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FullSize )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SmallSize )( 
            IPDFReader * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Language )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Language )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VersionEx )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_HaveSignature )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EvevtTeam )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_EvevtTeam )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MoveSignature )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CursorState )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CursorState )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindFirst )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FindNext )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnableUserTools )( 
            IPDFReader * This,
            /* [in] */ BSTR Index,
            /* [in] */ long Enabled);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnableUserMenus )( 
            IPDFReader * This,
            /* [in] */ BSTR Index,
            /* [in] */ long Enabled);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CopyRight )( 
            IPDFReader * This,
            /* [in] */ BSTR rhs);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Binary )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Binary )( 
            IPDFReader * This,
            /* [in] */ VARIANT Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportPages )( 
            IPDFReader * This,
            /* [in] */ BSTR FileName,
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [in] */ long Place,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeletePages )( 
            IPDFReader * This,
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SearchText )( 
            IPDFReader * This,
            /* [in] */ BSTR Text,
            /* [retval][out] */ BSTR *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ExtParam1 )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ExtParam1 )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ExtParam2 )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ExtParam2 )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ThirdTime )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ThirdTime )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureFileName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureFileName )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GrayDocument )( 
            IPDFReader * This,
            /* [in] */ BSTR ExParam,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportFieldValue )( 
            IPDFReader * This,
            /* [in] */ BSTR FieldName,
            /* [in] */ BSTR FieldValue,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ExportFieldValue )( 
            IPDFReader * This,
            /* [in] */ BSTR FieldName,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportImagePage )( 
            IPDFReader * This,
            /* [in] */ BSTR FileName,
            /* [in] */ long Zoom,
            /* [in] */ long isMapping,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportTemplate )( 
            IPDFReader * This,
            /* [in] */ BSTR XML,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveAccessory )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_FullScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_FullScreen )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoPreviousScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoNextScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GotoViewSignature )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CancelSignature )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveLocalFileEx )( 
            IPDFReader * This,
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR Ext1,
            /* [in] */ BSTR Ext2,
            /* [in] */ BSTR Ext3,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenLocalFileEx )( 
            IPDFReader * This,
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR LocalPath,
            /* [in] */ BSTR Ext1,
            /* [in] */ BSTR Ext2,
            /* [in] */ BSTR Ext3,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetMAC )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetIP )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *HandWriter )( 
            IPDFReader * This,
            /* [in] */ long type,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EnableHandWriter )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_EnableHandWriter )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImage )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR Image,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertText )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR Text,
            /* [in] */ long fontSize,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageByCursor )( 
            IPDFReader * This,
            /* [in] */ BSTR Image,
            /* [in] */ long isURL,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LockScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnlockScreen )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetCoordinate )( 
            IPDFReader * This,
            /* [in] */ BSTR Value,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCoordinate )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SeriesSignature )( 
            IPDFReader * This,
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ShowSearchDlg )( 
            IPDFReader * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowSchedule )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowSchedule )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AllowSignName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AllowSignName )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeleteUserTools )( 
            IPDFReader * This,
            /* [in] */ BSTR Index);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeleteUserMenus )( 
            IPDFReader * This,
            /* [in] */ BSTR Index);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddComment )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ BSTR Text,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowPostil )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowPostil )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FastSignature )( 
            IPDFReader * This,
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AllowMoveAnnot )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AllowMoveAnnot )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebInsertImage )( 
            IPDFReader * This,
            /* [in] */ BSTR Value,
            /* [in] */ long PageNo,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ImportFieldValueByXML )( 
            IPDFReader * This,
            /* [in] */ BSTR sXML,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_EnableUpdating )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_EnableUpdating )( 
            IPDFReader * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSetScrollBarPos )( 
            IPDFReader * This,
            /* [in] */ long xPos,
            /* [in] */ long yPos,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetKeySN )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageByPosition )( 
            IPDFReader * This,
            /* [in] */ BSTR sName,
            /* [in] */ long mode,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR sImagePath,
            /* [in] */ long isURL,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebPrintEx )( 
            IPDFReader * This,
            /* [in] */ long Copies,
            /* [in] */ BSTR PrinterName,
            /* [in] */ BSTR PageArea,
            /* [in] */ VARIANT_BOOL ShowDlg,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTextPostilInfo )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DocumentModified )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TextCommentRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TextCommentRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CheckPdfHasSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR filePath,
            /* [retval][out] */ BSTR *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowPostilList )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowPostilList )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetSelectState )( 
            IPDFReader * This,
            /* [in] */ long state,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebDoffSealToImage )( 
            IPDFReader * This,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_LocalPrinterNameList )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_LocalPrinterDriverList )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebImageToPDF )( 
            IPDFReader * This,
            /* [in] */ BSTR sImagePath,
            /* [in] */ BSTR sPdfPath,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebPrintControl )( 
            IPDFReader * This,
            /* [in] */ BSTR PrinterName,
            /* [in] */ long MaxPrintCopies,
            /* [in] */ long PrintCopies,
            /* [in] */ BSTR PrintPage,
            /* [in] */ long ShowDlg,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureOutputFlags )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureOutputFlags )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *EnabledHideKeywords )( 
            IPDFReader * This,
            /* [in] */ long Ch,
            /* [in] */ VARIANT_BOOL Value,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AppendHideKeywords )( 
            IPDFReader * This,
            /* [in] */ BSTR Keywords);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveSignDataToLocal )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *lRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *LoadLocalSignData )( 
            IPDFReader * This,
            /* [in] */ BSTR strSignData,
            /* [retval][out] */ long *lRet);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UserID )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_UserID )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureMode )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureMode )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateBarcodeSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR barcodeString,
            /* [in] */ long bShowDlg,
            /* [in] */ BSTR SignPass,
            /* [in] */ long lStartPage,
            /* [in] */ long lEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lRet);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowDigitalSignature )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowDigitalSignature )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AppendRevision )( 
            IPDFReader * This,
            /* [in] */ BSTR Revision);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearRevisions )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentRevision )( 
            IPDFReader * This,
            /* [in] */ BSTR CustomData,
            /* [retval][out] */ BSTR *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_RevisionCount )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRevisionCustomData )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *sRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetCryptPassword )( 
            IPDFReader * This,
            /* [in] */ BSTR pwd,
            /* [retval][out] */ VARIANT_BOOL *lRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddImageText )( 
            IPDFReader * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ long fontSize,
            /* [in] */ long FontColor,
            /* [in] */ BSTR FontName,
            /* [in] */ BSTR Text);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearImageText )( 
            IPDFReader * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ImageTextEnabled )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ImageTextEnabled )( 
            IPDFReader * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebAddBookmark )( 
            IPDFReader * This,
            /* [in] */ BSTR strValue,
            /* [retval][out] */ VARIANT_BOOL *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebDelBookmark )( 
            IPDFReader * This,
            /* [in] */ BSTR strValue,
            /* [retval][out] */ VARIANT_BOOL *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebGetFilePath )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignatureByName )( 
            IPDFReader * This,
            /* [in] */ BSTR sealName,
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ BSTR Password,
            /* [in] */ long mode,
            /* [in] */ BSTR posText,
            /* [in] */ BSTR protectArea,
            /* [retval][out] */ long *lRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateRayCodeSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR SignPass,
            /* [in] */ long PageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateQRCodeSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR QRCodeString,
            /* [in] */ long bShowDlg,
            /* [in] */ BSTR SigPass,
            /* [in] */ long lStartPage,
            /* [in] */ long lEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AppCode )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AppCode )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IsPrintControl )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IsPrintControl )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ShowToolBarHint )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ShowToolBarHint )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertMoveText )( 
            IPDFReader * This,
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ BSTR Pos,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ImageAnnotDelRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ImageAnnotDelRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ImageAnnotMoveRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ImageAnnotMoveRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignatureByImage )( 
            IPDFReader * This,
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertMoveTextExt )( 
            IPDFReader * This,
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Pos,
            /* [in] */ long PosType,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignatureFrom )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignatureFrom )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UserRole )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_UserRole )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GoToTextComment )( 
            IPDFReader * This,
            /* [in] */ BSTR TextID,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FastSignatureByImage )( 
            IPDFReader * This,
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IsShowInputBox )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IsShowInputBox )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetSpecificSignCount )( 
            IPDFReader * This,
            /* [in] */ BSTR Pages,
            /* [in] */ long SignType,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_PrintConfig )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_PrintConfig )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_WaterMarkVisible )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_WaterMarkVisible )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignaturePages )( 
            IPDFReader * This,
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Pages,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GoToText )( 
            IPDFReader * This,
            /* [in] */ BSTR Text,
            /* [in] */ long Page,
            /* [in] */ VARIANT_BOOL Case,
            /* [in] */ VARIANT_BOOL UpDown,
            /* [in] */ VARIANT_BOOL Selected,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsPagesSigned )( 
            IPDFReader * This,
            /* [in] */ BSTR Pages,
            /* [in] */ long SignType,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OpenStream )( 
            IPDFReader * This,
            /* [in] */ VARIANT *AStream,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveStream )( 
            IPDFReader * This,
            /* [out] */ VARIANT *AStream,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetUserPassWord )( 
            IPDFReader * This,
            /* [in] */ BSTR Password,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DBSignType )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DBSignType )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageByCursorExt )( 
            IPDFReader * This,
            /* [in] */ BSTR Image,
            /* [in] */ long isURL,
            /* [in] */ long isTrans,
            /* [in] */ long actWidth,
            /* [in] */ long actHeight,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetDocumentID )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ServerURL )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ServerURL )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPublicInfo )( 
            IPDFReader * This,
            /* [in] */ long type,
            /* [in] */ BSTR Value,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPublicInfo )( 
            IPDFReader * This,
            /* [in] */ long type,
            /* [retval][out] */ BSTR *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CUSTOMPARAMS )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CUSTOMPARAMS )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTextPosition )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ BSTR Text,
            /* [in] */ VARIANT_BOOL Case,
            /* [in] */ long PType,
            /* [retval][out] */ BSTR *sInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetAnnotTextFile )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeletePagesExt )( 
            IPDFReader * This,
            /* [in] */ long Start,
            /* [in] */ long Trail,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetAnnotString )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddCommentExt )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR Text,
            /* [in] */ BSTR CTime,
            /* [in] */ BSTR MTime,
            /* [in] */ BSTR UName,
            /* [in] */ BSTR UId,
            /* [in] */ BSTR TId,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StartRect )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRectInfo )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *sInfo);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageByString )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ BSTR CTime,
            /* [in] */ BSTR MTime,
            /* [in] */ BSTR UName,
            /* [in] */ BSTR UId,
            /* [in] */ BSTR strPic,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR PId,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPostilPenColor )( 
            IPDFReader * This,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetPostilPenWidth )( 
            IPDFReader * This,
            /* [in] */ long pWidth,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CancelPostil )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DrawRect )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X1,
            /* [in] */ float Y1,
            /* [in] */ float X2,
            /* [in] */ float Y2,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldNames )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *strNames);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetBookMarks )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *strBookMarks);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GoToAnnot )( 
            IPDFReader * This,
            /* [in] */ BSTR strID,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetCPUID )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetHarDiskID )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *strResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_IsLocalPrint )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_IsLocalPrint )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageByPositionExt )( 
            IPDFReader * This,
            /* [in] */ BSTR strLocationInfo,
            /* [in] */ long mode,
            /* [in] */ long nStartPage,
            /* [in] */ long nEndPage,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR strImagePath,
            /* [in] */ long isURL,
            /* [in] */ float TranPre,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignatureByImageExt )( 
            IPDFReader * This,
            /* [in] */ BSTR imageFile,
            /* [in] */ BSTR SignPass,
            /* [in] */ VARIANT_BOOL bProtected,
            /* [in] */ long nStartPageNo,
            /* [in] */ long nEndPageNo,
            /* [in] */ long mode,
            /* [in] */ BSTR Position,
            /* [in] */ float TranPre,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MakeDocOWP )( 
            IPDFReader * This,
            /* [in] */ BSTR OWP,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CommentWindow )( 
            IPDFReader * This,
            /* [in] */ int AllOpen,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateBarCodeImage )( 
            IPDFReader * This,
            /* [in] */ BSTR BarCode,
            /* [in] */ long StartPage,
            /* [in] */ long EndPage,
            /* [in] */ long mode,
            /* [in] */ BSTR Pos,
            /* [in] */ long nType,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FileSize )( 
            IPDFReader * This,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SeriesSignatureExt )( 
            IPDFReader * This,
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [in] */ double ZoomPercent,
            /* [in] */ double rDegree,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveLocalFileNoSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR FileName,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *InsertImageExt )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X,
            /* [in] */ float Y,
            /* [in] */ float Width,
            /* [in] */ float Height,
            /* [in] */ BSTR Image,
            /* [in] */ VARIANT_BOOL Tback,
            /* [in] */ float dTran,
            /* [in] */ float Rotate,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTextPositionAll )( 
            IPDFReader * This,
            /* [in] */ BSTR strText,
            /* [in] */ BSTR strFileName,
            /* [retval][out] */ BSTR *strInf);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateSignatureByString )( 
            IPDFReader * This,
            /* [in] */ BSTR strInput,
            /* [in] */ long nPage,
            /* [in] */ BSTR Pos,
            /* [in] */ BSTR FName,
            /* [in] */ long FSize,
            /* [in] */ long RColor,
            /* [in] */ long GColor,
            /* [in] */ long BColor,
            /* [in] */ long mode,
            /* [retval][out] */ long *lResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AnnotCoordinate )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TSServerUrl )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSServerUrl )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSUser )( 
            IPDFReader * This,
            /* [in] */ BSTR rhs);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TSPwd )( 
            IPDFReader * This,
            /* [in] */ BSTR rhs);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignSerial )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SignSerialEnabled )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SignSerialEnabled )( 
            IPDFReader * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearImageSignSerial )( 
            IPDFReader * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddImageSignSerial )( 
            IPDFReader * This,
            /* [in] */ long fontSize,
            /* [in] */ long FontColor,
            /* [in] */ BSTR FontName,
            /* [in] */ BSTR SignSerial);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DrawRectExt )( 
            IPDFReader * This,
            /* [in] */ long PageNo,
            /* [in] */ float X1,
            /* [in] */ float Y1,
            /* [in] */ float X2,
            /* [in] */ float Y2,
            /* [in] */ long ishighlight,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CommentTextMoveRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CommentTextMoveRight )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRealSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR strParam,
            /* [retval][out] */ BSTR *strResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateStraddleSignature )( 
            IPDFReader * This,
            /* [in] */ long SignIndex,
            /* [in] */ BSTR SignPass,
            /* [in] */ BSTR Position,
            /* [in] */ long isBialteral,
            /* [in] */ long EvenOrOdd,
            /* [in] */ BSTR strRate,
            /* [in] */ BSTR Area,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetFieldByName )( 
            IPDFReader * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFieldByName )( 
            IPDFReader * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ BSTR *strResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearFieldByName )( 
            IPDFReader * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *MergeRealSignature )( 
            IPDFReader * This,
            /* [in] */ BSTR strFileName,
            /* [in] */ BSTR strSignInfo,
            /* [retval][out] */ long *lResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SaveFileToBase64 )( 
            IPDFReader * This,
            /* [in] */ long type,
            /* [retval][out] */ BSTR *strResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebOpenBase64 )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebSaveBase64 )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CustomPdfDocInfo )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CustomPdfDocInfo )( 
            IPDFReader * This,
            /* [in] */ BSTR Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *WebFastSave )( 
            IPDFReader * This,
            /* [retval][out] */ long *bResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BufSize )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BufSize )( 
            IPDFReader * This,
            /* [in] */ long Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SignatureCountExt )( 
            IPDFReader * This,
            /* [in] */ BSTR strName,
            /* [retval][out] */ long *Result);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetSignIfo )( 
            IPDFReader * This,
            /* [in] */ long nSigIndex,
            /* [in] */ BSTR strName,
            /* [retval][out] */ BSTR *sResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetSignaturePos )( 
            IPDFReader * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *strResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *FastSeriesSignature )( 
            IPDFReader * This,
            /* [in] */ long StartPageNo,
            /* [in] */ long EndPageNo,
            /* [in] */ long Index,
            /* [in] */ BSTR Pass,
            /* [in] */ long mode,
            /* [in] */ BSTR Postil,
            /* [in] */ BSTR Area,
            /* [in] */ long ReferencePoint,
            /* [retval][out] */ long *Result);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_isCopyRight )( 
            IPDFReader * This,
            /* [retval][out] */ long *Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelectedBookMarkName )( 
            IPDFReader * This,
            /* [retval][out] */ BSTR *Value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PrintWaterMark )( 
            IPDFReader * This,
            /* [in] */ BSTR strContent,
            /* [in] */ BSTR strName,
            /* [in] */ long nFSize,
            /* [in] */ long nFRColor,
            /* [in] */ long nFGColor,
            /* [in] */ long nFBColor,
            /* [in] */ long nFRotate,
            /* [retval][out] */ long *lResult);
        
        END_INTERFACE
    } IPDFReaderVtbl;

    interface IPDFReader
    {
        CONST_VTBL struct IPDFReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDFReader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPDFReader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPDFReader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPDFReader_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPDFReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPDFReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPDFReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPDFReader_get_Visible(This,Value)	\
    ( (This)->lpVtbl -> get_Visible(This,Value) ) 

#define IPDFReader_put_Visible(This,Value)	\
    ( (This)->lpVtbl -> put_Visible(This,Value) ) 

#define IPDFReader_get_Enabled(This,Value)	\
    ( (This)->lpVtbl -> get_Enabled(This,Value) ) 

#define IPDFReader_put_Enabled(This,Value)	\
    ( (This)->lpVtbl -> put_Enabled(This,Value) ) 

#define IPDFReader_AboutBox(This)	\
    ( (This)->lpVtbl -> AboutBox(This) ) 

#define IPDFReader_get_WebUrl(This,Value)	\
    ( (This)->lpVtbl -> get_WebUrl(This,Value) ) 

#define IPDFReader_put_WebUrl(This,Value)	\
    ( (This)->lpVtbl -> put_WebUrl(This,Value) ) 

#define IPDFReader_get_RecordID(This,Value)	\
    ( (This)->lpVtbl -> get_RecordID(This,Value) ) 

#define IPDFReader_put_RecordID(This,Value)	\
    ( (This)->lpVtbl -> put_RecordID(This,Value) ) 

#define IPDFReader_get_FileName(This,Value)	\
    ( (This)->lpVtbl -> get_FileName(This,Value) ) 

#define IPDFReader_put_FileName(This,Value)	\
    ( (This)->lpVtbl -> put_FileName(This,Value) ) 

#define IPDFReader_get_UserName(This,Value)	\
    ( (This)->lpVtbl -> get_UserName(This,Value) ) 

#define IPDFReader_put_UserName(This,Value)	\
    ( (This)->lpVtbl -> put_UserName(This,Value) ) 

#define IPDFReader_get_ShowTools(This,Value)	\
    ( (This)->lpVtbl -> get_ShowTools(This,Value) ) 

#define IPDFReader_put_ShowTools(This,Value)	\
    ( (This)->lpVtbl -> put_ShowTools(This,Value) ) 

#define IPDFReader_get_Status(This,Value)	\
    ( (This)->lpVtbl -> get_Status(This,Value) ) 

#define IPDFReader_put_ExtParam(This,rhs)	\
    ( (This)->lpVtbl -> put_ExtParam(This,rhs) ) 

#define IPDFReader_get_SaveRight(This,Value)	\
    ( (This)->lpVtbl -> get_SaveRight(This,Value) ) 

#define IPDFReader_put_SaveRight(This,Value)	\
    ( (This)->lpVtbl -> put_SaveRight(This,Value) ) 

#define IPDFReader_get_PrintRight(This,Value)	\
    ( (This)->lpVtbl -> get_PrintRight(This,Value) ) 

#define IPDFReader_put_PrintRight(This,Value)	\
    ( (This)->lpVtbl -> put_PrintRight(This,Value) ) 

#define IPDFReader_get_DisplayMode(This,Value)	\
    ( (This)->lpVtbl -> get_DisplayMode(This,Value) ) 

#define IPDFReader_put_DisplayMode(This,Value)	\
    ( (This)->lpVtbl -> put_DisplayMode(This,Value) ) 

#define IPDFReader_get_Zoom(This,Value)	\
    ( (This)->lpVtbl -> get_Zoom(This,Value) ) 

#define IPDFReader_put_Zoom(This,Value)	\
    ( (This)->lpVtbl -> put_Zoom(This,Value) ) 

#define IPDFReader_get_Rotate(This,Value)	\
    ( (This)->lpVtbl -> get_Rotate(This,Value) ) 

#define IPDFReader_put_Rotate(This,Value)	\
    ( (This)->lpVtbl -> put_Rotate(This,Value) ) 

#define IPDFReader_get_PageCount(This,Value)	\
    ( (This)->lpVtbl -> get_PageCount(This,Value) ) 

#define IPDFReader_get_CurPage(This,Value)	\
    ( (This)->lpVtbl -> get_CurPage(This,Value) ) 

#define IPDFReader_put_CurPage(This,Value)	\
    ( (This)->lpVtbl -> put_CurPage(This,Value) ) 

#define IPDFReader_get_AlterUser(This,Value)	\
    ( (This)->lpVtbl -> get_AlterUser(This,Value) ) 

#define IPDFReader_put_AlterUser(This,Value)	\
    ( (This)->lpVtbl -> put_AlterUser(This,Value) ) 

#define IPDFReader_get_LocalFileName(This,Value)	\
    ( (This)->lpVtbl -> get_LocalFileName(This,Value) ) 

#define IPDFReader_get_MaxFileSize(This,Value)	\
    ( (This)->lpVtbl -> get_MaxFileSize(This,Value) ) 

#define IPDFReader_put_MaxFileSize(This,Value)	\
    ( (This)->lpVtbl -> put_MaxFileSize(This,Value) ) 

#define IPDFReader_WebOpenUrlFile(This,sWebUrl,bResult)	\
    ( (This)->lpVtbl -> WebOpenUrlFile(This,sWebUrl,bResult) ) 

#define IPDFReader_WebDownLoadFile(This,sWebUrl,sFileName,bResult)	\
    ( (This)->lpVtbl -> WebDownLoadFile(This,sWebUrl,sFileName,bResult) ) 

#define IPDFReader_GotoFirstPage(This,bResult)	\
    ( (This)->lpVtbl -> GotoFirstPage(This,bResult) ) 

#define IPDFReader_GotoLastPage(This,bResult)	\
    ( (This)->lpVtbl -> GotoLastPage(This,bResult) ) 

#define IPDFReader_GotoPreviousPage(This,bResult)	\
    ( (This)->lpVtbl -> GotoPreviousPage(This,bResult) ) 

#define IPDFReader_GotoNextPage(This,bResult)	\
    ( (This)->lpVtbl -> GotoNextPage(This,bResult) ) 

#define IPDFReader_WebOpen(This,bResult)	\
    ( (This)->lpVtbl -> WebOpen(This,bResult) ) 

#define IPDFReader_WebSave(This,bResult)	\
    ( (This)->lpVtbl -> WebSave(This,bResult) ) 

#define IPDFReader_WebClose(This,bResult)	\
    ( (This)->lpVtbl -> WebClose(This,bResult) ) 

#define IPDFReader_WebSaveLocal(This,bResult)	\
    ( (This)->lpVtbl -> WebSaveLocal(This,bResult) ) 

#define IPDFReader_WebOpenLocal(This,bResult)	\
    ( (This)->lpVtbl -> WebOpenLocal(This,bResult) ) 

#define IPDFReader_WebSaveLocalDialog(This,sResult)	\
    ( (This)->lpVtbl -> WebSaveLocalDialog(This,sResult) ) 

#define IPDFReader_WebOpenLocalDialog(This,sResult)	\
    ( (This)->lpVtbl -> WebOpenLocalDialog(This,sResult) ) 

#define IPDFReader_WebSaveLocalFile(This,sFileName,bResult)	\
    ( (This)->lpVtbl -> WebSaveLocalFile(This,sFileName,bResult) ) 

#define IPDFReader_WebOpenLocalFile(This,sFileName,bResult)	\
    ( (This)->lpVtbl -> WebOpenLocalFile(This,sFileName,bResult) ) 

#define IPDFReader_WebSetMsgByName(This,sFieldName,sFieldValue,bResult)	\
    ( (This)->lpVtbl -> WebSetMsgByName(This,sFieldName,sFieldValue,bResult) ) 

#define IPDFReader_WebGetMsgByName(This,sFieldName,sResult)	\
    ( (This)->lpVtbl -> WebGetMsgByName(This,sFieldName,sResult) ) 

#define IPDFReader_WebClearMessage(This,bResult)	\
    ( (This)->lpVtbl -> WebClearMessage(This,bResult) ) 

#define IPDFReader_WebSendMessage(This,bResult)	\
    ( (This)->lpVtbl -> WebSendMessage(This,bResult) ) 

#define IPDFReader_WebPrint(This,Copies,PrintName,FromPage,ToPage,ShowDlg,bResult)	\
    ( (This)->lpVtbl -> WebPrint(This,Copies,PrintName,FromPage,ToPage,ShowDlg,bResult) ) 

#define IPDFReader_EnableTools(This,sTools,bEnable,bResult)	\
    ( (This)->lpVtbl -> EnableTools(This,sTools,bEnable,bResult) ) 

#define IPDFReader_get_ShowMarks(This,Value)	\
    ( (This)->lpVtbl -> get_ShowMarks(This,Value) ) 

#define IPDFReader_put_ShowMarks(This,Value)	\
    ( (This)->lpVtbl -> put_ShowMarks(This,Value) ) 

#define IPDFReader_get_ShowMenus(This,Value)	\
    ( (This)->lpVtbl -> get_ShowMenus(This,Value) ) 

#define IPDFReader_put_ShowMenus(This,Value)	\
    ( (This)->lpVtbl -> put_ShowMenus(This,Value) ) 

#define IPDFReader_get_ShowState(This,Value)	\
    ( (This)->lpVtbl -> get_ShowState(This,Value) ) 

#define IPDFReader_put_ShowState(This,Value)	\
    ( (This)->lpVtbl -> put_ShowState(This,Value) ) 

#define IPDFReader_get_ShowSides(This,Value)	\
    ( (This)->lpVtbl -> get_ShowSides(This,Value) ) 

#define IPDFReader_put_ShowSides(This,Value)	\
    ( (This)->lpVtbl -> put_ShowSides(This,Value) ) 

#define IPDFReader_CreateSignature(This,SignIndex,SignPass,PageNo,mode,Position,Area,Result)	\
    ( (This)->lpVtbl -> CreateSignature(This,SignIndex,SignPass,PageNo,mode,Position,Area,Result) ) 

#define IPDFReader_ShowSignDlg(This,type,Result)	\
    ( (This)->lpVtbl -> ShowSignDlg(This,type,Result) ) 

#define IPDFReader_ShowCheckDlg(This,Result)	\
    ( (This)->lpVtbl -> ShowCheckDlg(This,Result) ) 

#define IPDFReader_ShowParamDlg(This,Result)	\
    ( (This)->lpVtbl -> ShowParamDlg(This,Result) ) 

#define IPDFReader_SignatureNames(This,Result)	\
    ( (This)->lpVtbl -> SignatureNames(This,Result) ) 

#define IPDFReader_SignatureItem(This,Index,Result)	\
    ( (This)->lpVtbl -> SignatureItem(This,Index,Result) ) 

#define IPDFReader_SignatureCount(This,Result)	\
    ( (This)->lpVtbl -> SignatureCount(This,Result) ) 

#define IPDFReader_CertificateSign(This,Index,CardPin,Result)	\
    ( (This)->lpVtbl -> CertificateSign(This,Index,CardPin,Result) ) 

#define IPDFReader_DeleteSignature(This,Password,Result)	\
    ( (This)->lpVtbl -> DeleteSignature(This,Password,Result) ) 

#define IPDFReader_GetErrorString(This,Code,Result)	\
    ( (This)->lpVtbl -> GetErrorString(This,Code,Result) ) 

#define IPDFReader_VerifyPin(This,CardPin,Result)	\
    ( (This)->lpVtbl -> VerifyPin(This,CardPin,Result) ) 

#define IPDFReader_GetPageSize(This,PageNo,Index,Result)	\
    ( (This)->lpVtbl -> GetPageSize(This,PageNo,Index,Result) ) 

#define IPDFReader_GetKeyCount(This,Result)	\
    ( (This)->lpVtbl -> GetKeyCount(This,Result) ) 

#define IPDFReader_WateMark(This,StartPage,EndPage,Text,nstrok,fontSize,Rotate,Back,X,Y,Result)	\
    ( (This)->lpVtbl -> WateMark(This,StartPage,EndPage,Text,nstrok,fontSize,Rotate,Back,X,Y,Result) ) 

#define IPDFReader_get_PrintStatus(This,Value)	\
    ( (This)->lpVtbl -> get_PrintStatus(This,Value) ) 

#define IPDFReader_get_SaveStatus(This,Value)	\
    ( (This)->lpVtbl -> get_SaveStatus(This,Value) ) 

#define IPDFReader_get_EditStatus(This,Value)	\
    ( (This)->lpVtbl -> get_EditStatus(This,Value) ) 

#define IPDFReader_get_CopyStatus(This,Value)	\
    ( (This)->lpVtbl -> get_CopyStatus(This,Value) ) 

#define IPDFReader_get_ShowSigns(This,Value)	\
    ( (This)->lpVtbl -> get_ShowSigns(This,Value) ) 

#define IPDFReader_put_ShowSigns(This,Value)	\
    ( (This)->lpVtbl -> put_ShowSigns(This,Value) ) 

#define IPDFReader_get_SideWidth(This,Value)	\
    ( (This)->lpVtbl -> get_SideWidth(This,Value) ) 

#define IPDFReader_put_SideWidth(This,Value)	\
    ( (This)->lpVtbl -> put_SideWidth(This,Value) ) 

#define IPDFReader_EnablePages(This,Pages,Enable,Text,Result)	\
    ( (This)->lpVtbl -> EnablePages(This,Pages,Enable,Text,Result) ) 

#define IPDFReader_get_FileType(This,Value)	\
    ( (This)->lpVtbl -> get_FileType(This,Value) ) 

#define IPDFReader_put_FileType(This,Value)	\
    ( (This)->lpVtbl -> put_FileType(This,Value) ) 

#define IPDFReader_get_isOpen(This,Value)	\
    ( (This)->lpVtbl -> get_isOpen(This,Value) ) 

#define IPDFReader_ShedCryptoDocument(This,IsSaveAs,Result)	\
    ( (This)->lpVtbl -> ShedCryptoDocument(This,IsSaveAs,Result) ) 

#define IPDFReader_get_ShowTitle(This,Value)	\
    ( (This)->lpVtbl -> get_ShowTitle(This,Value) ) 

#define IPDFReader_put_ShowTitle(This,Value)	\
    ( (This)->lpVtbl -> put_ShowTitle(This,Value) ) 

#define IPDFReader_get_SideColor(This,Value)	\
    ( (This)->lpVtbl -> get_SideColor(This,Value) ) 

#define IPDFReader_put_SideColor(This,Value)	\
    ( (This)->lpVtbl -> put_SideColor(This,Value) ) 

#define IPDFReader_SaveSignData(This,res)	\
    ( (This)->lpVtbl -> SaveSignData(This,res) ) 

#define IPDFReader_LoadSignData(This,res)	\
    ( (This)->lpVtbl -> LoadSignData(This,res) ) 

#define IPDFReader_GotoBookMark(This,BookMark,Result)	\
    ( (This)->lpVtbl -> GotoBookMark(This,BookMark,Result) ) 

#define IPDFReader_SetPublicParam(This,Name,Value,HeaderValue,Result)	\
    ( (This)->lpVtbl -> SetPublicParam(This,Name,Value,HeaderValue,Result) ) 

#define IPDFReader_SetSignatureParam(This,Name,Value,HeaderValue,Result)	\
    ( (This)->lpVtbl -> SetSignatureParam(This,Name,Value,HeaderValue,Result) ) 

#define IPDFReader_get_ContentText(This,Value)	\
    ( (This)->lpVtbl -> get_ContentText(This,Value) ) 

#define IPDFReader_get_PrnScreen(This,Value)	\
    ( (This)->lpVtbl -> get_PrnScreen(This,Value) ) 

#define IPDFReader_put_PrnScreen(This,Value)	\
    ( (This)->lpVtbl -> put_PrnScreen(This,Value) ) 

#define IPDFReader_AppendMenu(This,Index,Caption)	\
    ( (This)->lpVtbl -> AppendMenu(This,Index,Caption) ) 

#define IPDFReader_AppendTools(This,Index,Caption,Icon)	\
    ( (This)->lpVtbl -> AppendTools(This,Index,Caption,Icon) ) 

#define IPDFReader_FullSize(This)	\
    ( (This)->lpVtbl -> FullSize(This) ) 

#define IPDFReader_SmallSize(This)	\
    ( (This)->lpVtbl -> SmallSize(This) ) 

#define IPDFReader_get_Language(This,Value)	\
    ( (This)->lpVtbl -> get_Language(This,Value) ) 

#define IPDFReader_put_Language(This,Value)	\
    ( (This)->lpVtbl -> put_Language(This,Value) ) 

#define IPDFReader_get_VersionEx(This,Value)	\
    ( (This)->lpVtbl -> get_VersionEx(This,Value) ) 

#define IPDFReader_get_Version(This,Value)	\
    ( (This)->lpVtbl -> get_Version(This,Value) ) 

#define IPDFReader_get_HaveSignature(This,Value)	\
    ( (This)->lpVtbl -> get_HaveSignature(This,Value) ) 

#define IPDFReader_get_EvevtTeam(This,Value)	\
    ( (This)->lpVtbl -> get_EvevtTeam(This,Value) ) 

#define IPDFReader_put_EvevtTeam(This,Value)	\
    ( (This)->lpVtbl -> put_EvevtTeam(This,Value) ) 

#define IPDFReader_MoveSignature(This,Index,Pass,mode,Position,Result)	\
    ( (This)->lpVtbl -> MoveSignature(This,Index,Pass,mode,Position,Result) ) 

#define IPDFReader_get_CursorState(This,Value)	\
    ( (This)->lpVtbl -> get_CursorState(This,Value) ) 

#define IPDFReader_put_CursorState(This,Value)	\
    ( (This)->lpVtbl -> put_CursorState(This,Value) ) 

#define IPDFReader_FindFirst(This)	\
    ( (This)->lpVtbl -> FindFirst(This) ) 

#define IPDFReader_FindNext(This)	\
    ( (This)->lpVtbl -> FindNext(This) ) 

#define IPDFReader_EnableUserTools(This,Index,Enabled)	\
    ( (This)->lpVtbl -> EnableUserTools(This,Index,Enabled) ) 

#define IPDFReader_EnableUserMenus(This,Index,Enabled)	\
    ( (This)->lpVtbl -> EnableUserMenus(This,Index,Enabled) ) 

#define IPDFReader_put_CopyRight(This,rhs)	\
    ( (This)->lpVtbl -> put_CopyRight(This,rhs) ) 

#define IPDFReader_get_Binary(This,Value)	\
    ( (This)->lpVtbl -> get_Binary(This,Value) ) 

#define IPDFReader_put_Binary(This,Value)	\
    ( (This)->lpVtbl -> put_Binary(This,Value) ) 

#define IPDFReader_ImportPages(This,FileName,Start,Trail,Place,Result)	\
    ( (This)->lpVtbl -> ImportPages(This,FileName,Start,Trail,Place,Result) ) 

#define IPDFReader_DeletePages(This,Start,Trail,Result)	\
    ( (This)->lpVtbl -> DeletePages(This,Start,Trail,Result) ) 

#define IPDFReader_SearchText(This,Text,Result)	\
    ( (This)->lpVtbl -> SearchText(This,Text,Result) ) 

#define IPDFReader_get_ExtParam1(This,Value)	\
    ( (This)->lpVtbl -> get_ExtParam1(This,Value) ) 

#define IPDFReader_put_ExtParam1(This,Value)	\
    ( (This)->lpVtbl -> put_ExtParam1(This,Value) ) 

#define IPDFReader_get_ExtParam2(This,Value)	\
    ( (This)->lpVtbl -> get_ExtParam2(This,Value) ) 

#define IPDFReader_put_ExtParam2(This,Value)	\
    ( (This)->lpVtbl -> put_ExtParam2(This,Value) ) 

#define IPDFReader_get_ThirdTime(This,Value)	\
    ( (This)->lpVtbl -> get_ThirdTime(This,Value) ) 

#define IPDFReader_put_ThirdTime(This,Value)	\
    ( (This)->lpVtbl -> put_ThirdTime(This,Value) ) 

#define IPDFReader_get_SignatureFileName(This,Value)	\
    ( (This)->lpVtbl -> get_SignatureFileName(This,Value) ) 

#define IPDFReader_put_SignatureFileName(This,Value)	\
    ( (This)->lpVtbl -> put_SignatureFileName(This,Value) ) 

#define IPDFReader_GrayDocument(This,ExParam,Result)	\
    ( (This)->lpVtbl -> GrayDocument(This,ExParam,Result) ) 

#define IPDFReader_ImportFieldValue(This,FieldName,FieldValue,Result)	\
    ( (This)->lpVtbl -> ImportFieldValue(This,FieldName,FieldValue,Result) ) 

#define IPDFReader_ExportFieldValue(This,FieldName,Result)	\
    ( (This)->lpVtbl -> ExportFieldValue(This,FieldName,Result) ) 

#define IPDFReader_ImportImagePage(This,FileName,Zoom,isMapping,Result)	\
    ( (This)->lpVtbl -> ImportImagePage(This,FileName,Zoom,isMapping,Result) ) 

#define IPDFReader_ImportTemplate(This,XML,Result)	\
    ( (This)->lpVtbl -> ImportTemplate(This,XML,Result) ) 

#define IPDFReader_WebSaveAccessory(This,bResult)	\
    ( (This)->lpVtbl -> WebSaveAccessory(This,bResult) ) 

#define IPDFReader_get_FullScreen(This,Value)	\
    ( (This)->lpVtbl -> get_FullScreen(This,Value) ) 

#define IPDFReader_put_FullScreen(This,Value)	\
    ( (This)->lpVtbl -> put_FullScreen(This,Value) ) 

#define IPDFReader_GotoPreviousScreen(This,Result)	\
    ( (This)->lpVtbl -> GotoPreviousScreen(This,Result) ) 

#define IPDFReader_GotoNextScreen(This,Result)	\
    ( (This)->lpVtbl -> GotoNextScreen(This,Result) ) 

#define IPDFReader_GotoViewSignature(This,Index,Result)	\
    ( (This)->lpVtbl -> GotoViewSignature(This,Index,Result) ) 

#define IPDFReader_CancelSignature(This)	\
    ( (This)->lpVtbl -> CancelSignature(This) ) 

#define IPDFReader_WebSaveLocalFileEx(This,FileName,Password,LocalPath,Ext1,Ext2,Ext3,Result)	\
    ( (This)->lpVtbl -> WebSaveLocalFileEx(This,FileName,Password,LocalPath,Ext1,Ext2,Ext3,Result) ) 

#define IPDFReader_WebOpenLocalFileEx(This,FileName,Password,LocalPath,Ext1,Ext2,Ext3,Result)	\
    ( (This)->lpVtbl -> WebOpenLocalFileEx(This,FileName,Password,LocalPath,Ext1,Ext2,Ext3,Result) ) 

#define IPDFReader_WebGetMAC(This,Result)	\
    ( (This)->lpVtbl -> WebGetMAC(This,Result) ) 

#define IPDFReader_WebGetIP(This,Result)	\
    ( (This)->lpVtbl -> WebGetIP(This,Result) ) 

#define IPDFReader_HandWriter(This,type,Result)	\
    ( (This)->lpVtbl -> HandWriter(This,type,Result) ) 

#define IPDFReader_get_EnableHandWriter(This,Value)	\
    ( (This)->lpVtbl -> get_EnableHandWriter(This,Value) ) 

#define IPDFReader_put_EnableHandWriter(This,Value)	\
    ( (This)->lpVtbl -> put_EnableHandWriter(This,Value) ) 

#define IPDFReader_InsertImage(This,PageNo,X,Y,Width,Height,Image,Result)	\
    ( (This)->lpVtbl -> InsertImage(This,PageNo,X,Y,Width,Height,Image,Result) ) 

#define IPDFReader_InsertText(This,PageNo,X,Y,Text,fontSize,Result)	\
    ( (This)->lpVtbl -> InsertText(This,PageNo,X,Y,Text,fontSize,Result) ) 

#define IPDFReader_InsertImageByCursor(This,Image,isURL,Result)	\
    ( (This)->lpVtbl -> InsertImageByCursor(This,Image,isURL,Result) ) 

#define IPDFReader_LockScreen(This,Result)	\
    ( (This)->lpVtbl -> LockScreen(This,Result) ) 

#define IPDFReader_UnlockScreen(This,Result)	\
    ( (This)->lpVtbl -> UnlockScreen(This,Result) ) 

#define IPDFReader_SetCoordinate(This,Value,Result)	\
    ( (This)->lpVtbl -> SetCoordinate(This,Value,Result) ) 

#define IPDFReader_GetCoordinate(This,Result)	\
    ( (This)->lpVtbl -> GetCoordinate(This,Result) ) 

#define IPDFReader_SeriesSignature(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,Result)	\
    ( (This)->lpVtbl -> SeriesSignature(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,Result) ) 

#define IPDFReader_ShowSearchDlg(This)	\
    ( (This)->lpVtbl -> ShowSearchDlg(This) ) 

#define IPDFReader_get_ShowSchedule(This,Value)	\
    ( (This)->lpVtbl -> get_ShowSchedule(This,Value) ) 

#define IPDFReader_put_ShowSchedule(This,Value)	\
    ( (This)->lpVtbl -> put_ShowSchedule(This,Value) ) 

#define IPDFReader_get_AllowSignName(This,Value)	\
    ( (This)->lpVtbl -> get_AllowSignName(This,Value) ) 

#define IPDFReader_put_AllowSignName(This,Value)	\
    ( (This)->lpVtbl -> put_AllowSignName(This,Value) ) 

#define IPDFReader_DeleteUserTools(This,Index)	\
    ( (This)->lpVtbl -> DeleteUserTools(This,Index) ) 

#define IPDFReader_DeleteUserMenus(This,Index)	\
    ( (This)->lpVtbl -> DeleteUserMenus(This,Index) ) 

#define IPDFReader_AddComment(This,PageNo,X,Y,Text,Result)	\
    ( (This)->lpVtbl -> AddComment(This,PageNo,X,Y,Text,Result) ) 

#define IPDFReader_get_ShowPostil(This,Value)	\
    ( (This)->lpVtbl -> get_ShowPostil(This,Value) ) 

#define IPDFReader_put_ShowPostil(This,Value)	\
    ( (This)->lpVtbl -> put_ShowPostil(This,Value) ) 

#define IPDFReader_FastSignature(This,SignIndex,SignPass,Area,Result)	\
    ( (This)->lpVtbl -> FastSignature(This,SignIndex,SignPass,Area,Result) ) 

#define IPDFReader_get_AllowMoveAnnot(This,Value)	\
    ( (This)->lpVtbl -> get_AllowMoveAnnot(This,Value) ) 

#define IPDFReader_put_AllowMoveAnnot(This,Value)	\
    ( (This)->lpVtbl -> put_AllowMoveAnnot(This,Value) ) 

#define IPDFReader_WebInsertImage(This,Value,PageNo,X,Y,Result)	\
    ( (This)->lpVtbl -> WebInsertImage(This,Value,PageNo,X,Y,Result) ) 

#define IPDFReader_ImportFieldValueByXML(This,sXML,lResult)	\
    ( (This)->lpVtbl -> ImportFieldValueByXML(This,sXML,lResult) ) 

#define IPDFReader_get_EnableUpdating(This,Value)	\
    ( (This)->lpVtbl -> get_EnableUpdating(This,Value) ) 

#define IPDFReader_put_EnableUpdating(This,Value)	\
    ( (This)->lpVtbl -> put_EnableUpdating(This,Value) ) 

#define IPDFReader_WebSetScrollBarPos(This,xPos,yPos,Result)	\
    ( (This)->lpVtbl -> WebSetScrollBarPos(This,xPos,yPos,Result) ) 

#define IPDFReader_WebGetKeySN(This,Result)	\
    ( (This)->lpVtbl -> WebGetKeySN(This,Result) ) 

#define IPDFReader_InsertImageByPosition(This,sName,mode,nStartPage,nEndPage,Width,Height,sImagePath,isURL,lResult)	\
    ( (This)->lpVtbl -> InsertImageByPosition(This,sName,mode,nStartPage,nEndPage,Width,Height,sImagePath,isURL,lResult) ) 

#define IPDFReader_WebPrintEx(This,Copies,PrinterName,PageArea,ShowDlg,lResult)	\
    ( (This)->lpVtbl -> WebPrintEx(This,Copies,PrinterName,PageArea,ShowDlg,lResult) ) 

#define IPDFReader_GetTextPostilInfo(This,sResult)	\
    ( (This)->lpVtbl -> GetTextPostilInfo(This,sResult) ) 

#define IPDFReader_get_DocumentModified(This,Value)	\
    ( (This)->lpVtbl -> get_DocumentModified(This,Value) ) 

#define IPDFReader_get_TextCommentRight(This,Value)	\
    ( (This)->lpVtbl -> get_TextCommentRight(This,Value) ) 

#define IPDFReader_put_TextCommentRight(This,Value)	\
    ( (This)->lpVtbl -> put_TextCommentRight(This,Value) ) 

#define IPDFReader_CheckPdfHasSignature(This,filePath,lResult)	\
    ( (This)->lpVtbl -> CheckPdfHasSignature(This,filePath,lResult) ) 

#define IPDFReader_get_ShowPostilList(This,Value)	\
    ( (This)->lpVtbl -> get_ShowPostilList(This,Value) ) 

#define IPDFReader_put_ShowPostilList(This,Value)	\
    ( (This)->lpVtbl -> put_ShowPostilList(This,Value) ) 

#define IPDFReader_SetSelectState(This,state,lResult)	\
    ( (This)->lpVtbl -> SetSelectState(This,state,lResult) ) 

#define IPDFReader_WebDoffSealToImage(This,lResult)	\
    ( (This)->lpVtbl -> WebDoffSealToImage(This,lResult) ) 

#define IPDFReader_get_LocalPrinterNameList(This,Value)	\
    ( (This)->lpVtbl -> get_LocalPrinterNameList(This,Value) ) 

#define IPDFReader_get_LocalPrinterDriverList(This,Value)	\
    ( (This)->lpVtbl -> get_LocalPrinterDriverList(This,Value) ) 

#define IPDFReader_WebImageToPDF(This,sImagePath,sPdfPath,lResult)	\
    ( (This)->lpVtbl -> WebImageToPDF(This,sImagePath,sPdfPath,lResult) ) 

#define IPDFReader_WebPrintControl(This,PrinterName,MaxPrintCopies,PrintCopies,PrintPage,ShowDlg,lResult)	\
    ( (This)->lpVtbl -> WebPrintControl(This,PrinterName,MaxPrintCopies,PrintCopies,PrintPage,ShowDlg,lResult) ) 

#define IPDFReader_get_SignatureOutputFlags(This,Value)	\
    ( (This)->lpVtbl -> get_SignatureOutputFlags(This,Value) ) 

#define IPDFReader_put_SignatureOutputFlags(This,Value)	\
    ( (This)->lpVtbl -> put_SignatureOutputFlags(This,Value) ) 

#define IPDFReader_EnabledHideKeywords(This,Ch,Value,Result)	\
    ( (This)->lpVtbl -> EnabledHideKeywords(This,Ch,Value,Result) ) 

#define IPDFReader_AppendHideKeywords(This,Keywords)	\
    ( (This)->lpVtbl -> AppendHideKeywords(This,Keywords) ) 

#define IPDFReader_SaveSignDataToLocal(This,lRet)	\
    ( (This)->lpVtbl -> SaveSignDataToLocal(This,lRet) ) 

#define IPDFReader_LoadLocalSignData(This,strSignData,lRet)	\
    ( (This)->lpVtbl -> LoadLocalSignData(This,strSignData,lRet) ) 

#define IPDFReader_get_UserID(This,Value)	\
    ( (This)->lpVtbl -> get_UserID(This,Value) ) 

#define IPDFReader_put_UserID(This,Value)	\
    ( (This)->lpVtbl -> put_UserID(This,Value) ) 

#define IPDFReader_get_SignatureMode(This,Value)	\
    ( (This)->lpVtbl -> get_SignatureMode(This,Value) ) 

#define IPDFReader_put_SignatureMode(This,Value)	\
    ( (This)->lpVtbl -> put_SignatureMode(This,Value) ) 

#define IPDFReader_CreateBarcodeSignature(This,barcodeString,bShowDlg,SignPass,lStartPage,lEndPage,mode,Position,Area,lRet)	\
    ( (This)->lpVtbl -> CreateBarcodeSignature(This,barcodeString,bShowDlg,SignPass,lStartPage,lEndPage,mode,Position,Area,lRet) ) 

#define IPDFReader_get_ShowDigitalSignature(This,Value)	\
    ( (This)->lpVtbl -> get_ShowDigitalSignature(This,Value) ) 

#define IPDFReader_put_ShowDigitalSignature(This,Value)	\
    ( (This)->lpVtbl -> put_ShowDigitalSignature(This,Value) ) 

#define IPDFReader_AppendRevision(This,Revision)	\
    ( (This)->lpVtbl -> AppendRevision(This,Revision) ) 

#define IPDFReader_ClearRevisions(This)	\
    ( (This)->lpVtbl -> ClearRevisions(This) ) 

#define IPDFReader_GetCurrentRevision(This,CustomData,Result)	\
    ( (This)->lpVtbl -> GetCurrentRevision(This,CustomData,Result) ) 

#define IPDFReader_get_RevisionCount(This,Value)	\
    ( (This)->lpVtbl -> get_RevisionCount(This,Value) ) 

#define IPDFReader_GetRevisionCustomData(This,Index,sRet)	\
    ( (This)->lpVtbl -> GetRevisionCustomData(This,Index,sRet) ) 

#define IPDFReader_SetCryptPassword(This,pwd,lRet)	\
    ( (This)->lpVtbl -> SetCryptPassword(This,pwd,lRet) ) 

#define IPDFReader_AddImageText(This,X,Y,fontSize,FontColor,FontName,Text)	\
    ( (This)->lpVtbl -> AddImageText(This,X,Y,fontSize,FontColor,FontName,Text) ) 

#define IPDFReader_ClearImageText(This)	\
    ( (This)->lpVtbl -> ClearImageText(This) ) 

#define IPDFReader_get_ImageTextEnabled(This,Value)	\
    ( (This)->lpVtbl -> get_ImageTextEnabled(This,Value) ) 

#define IPDFReader_put_ImageTextEnabled(This,Value)	\
    ( (This)->lpVtbl -> put_ImageTextEnabled(This,Value) ) 

#define IPDFReader_WebAddBookmark(This,strValue,lResult)	\
    ( (This)->lpVtbl -> WebAddBookmark(This,strValue,lResult) ) 

#define IPDFReader_WebDelBookmark(This,strValue,lResult)	\
    ( (This)->lpVtbl -> WebDelBookmark(This,strValue,lResult) ) 

#define IPDFReader_WebGetFilePath(This,Value)	\
    ( (This)->lpVtbl -> WebGetFilePath(This,Value) ) 

#define IPDFReader_CreateSignatureByName(This,sealName,StartPageNo,EndPageNo,Password,mode,posText,protectArea,lRet)	\
    ( (This)->lpVtbl -> CreateSignatureByName(This,sealName,StartPageNo,EndPageNo,Password,mode,posText,protectArea,lRet) ) 

#define IPDFReader_CreateRayCodeSignature(This,SignPass,PageNo,mode,Position,Area,Result)	\
    ( (This)->lpVtbl -> CreateRayCodeSignature(This,SignPass,PageNo,mode,Position,Area,Result) ) 

#define IPDFReader_CreateQRCodeSignature(This,QRCodeString,bShowDlg,SigPass,lStartPage,lEndPage,mode,Position,Area,lResult)	\
    ( (This)->lpVtbl -> CreateQRCodeSignature(This,QRCodeString,bShowDlg,SigPass,lStartPage,lEndPage,mode,Position,Area,lResult) ) 

#define IPDFReader_get_AppCode(This,Value)	\
    ( (This)->lpVtbl -> get_AppCode(This,Value) ) 

#define IPDFReader_put_AppCode(This,Value)	\
    ( (This)->lpVtbl -> put_AppCode(This,Value) ) 

#define IPDFReader_get_IsPrintControl(This,Value)	\
    ( (This)->lpVtbl -> get_IsPrintControl(This,Value) ) 

#define IPDFReader_put_IsPrintControl(This,Value)	\
    ( (This)->lpVtbl -> put_IsPrintControl(This,Value) ) 

#define IPDFReader_get_ShowToolBarHint(This,Value)	\
    ( (This)->lpVtbl -> get_ShowToolBarHint(This,Value) ) 

#define IPDFReader_put_ShowToolBarHint(This,Value)	\
    ( (This)->lpVtbl -> put_ShowToolBarHint(This,Value) ) 

#define IPDFReader_InsertMoveText(This,strInput,nPage,Pos,FName,FSize,RColor,GColor,BColor,lResult)	\
    ( (This)->lpVtbl -> InsertMoveText(This,strInput,nPage,Pos,FName,FSize,RColor,GColor,BColor,lResult) ) 

#define IPDFReader_get_ImageAnnotDelRight(This,Value)	\
    ( (This)->lpVtbl -> get_ImageAnnotDelRight(This,Value) ) 

#define IPDFReader_put_ImageAnnotDelRight(This,Value)	\
    ( (This)->lpVtbl -> put_ImageAnnotDelRight(This,Value) ) 

#define IPDFReader_get_ImageAnnotMoveRight(This,Value)	\
    ( (This)->lpVtbl -> get_ImageAnnotMoveRight(This,Value) ) 

#define IPDFReader_put_ImageAnnotMoveRight(This,Value)	\
    ( (This)->lpVtbl -> put_ImageAnnotMoveRight(This,Value) ) 

#define IPDFReader_CreateSignatureByImage(This,imageFile,SignPass,bProtected,nStartPage,nEndPage,mode,Position,Result)	\
    ( (This)->lpVtbl -> CreateSignatureByImage(This,imageFile,SignPass,bProtected,nStartPage,nEndPage,mode,Position,Result) ) 

#define IPDFReader_InsertMoveTextExt(This,strInput,nPage,mode,Pos,PosType,FName,FSize,RColor,GColor,BColor,lResult)	\
    ( (This)->lpVtbl -> InsertMoveTextExt(This,strInput,nPage,mode,Pos,PosType,FName,FSize,RColor,GColor,BColor,lResult) ) 

#define IPDFReader_get_SignatureFrom(This,Value)	\
    ( (This)->lpVtbl -> get_SignatureFrom(This,Value) ) 

#define IPDFReader_put_SignatureFrom(This,Value)	\
    ( (This)->lpVtbl -> put_SignatureFrom(This,Value) ) 

#define IPDFReader_get_UserRole(This,Value)	\
    ( (This)->lpVtbl -> get_UserRole(This,Value) ) 

#define IPDFReader_put_UserRole(This,Value)	\
    ( (This)->lpVtbl -> put_UserRole(This,Value) ) 

#define IPDFReader_GoToTextComment(This,TextID,lResult)	\
    ( (This)->lpVtbl -> GoToTextComment(This,TextID,lResult) ) 

#define IPDFReader_FastSignatureByImage(This,imageFile,SignPass,bProtected,Result)	\
    ( (This)->lpVtbl -> FastSignatureByImage(This,imageFile,SignPass,bProtected,Result) ) 

#define IPDFReader_get_IsShowInputBox(This,Value)	\
    ( (This)->lpVtbl -> get_IsShowInputBox(This,Value) ) 

#define IPDFReader_put_IsShowInputBox(This,Value)	\
    ( (This)->lpVtbl -> put_IsShowInputBox(This,Value) ) 

#define IPDFReader_GetSpecificSignCount(This,Pages,SignType,Result)	\
    ( (This)->lpVtbl -> GetSpecificSignCount(This,Pages,SignType,Result) ) 

#define IPDFReader_get_PrintConfig(This,Value)	\
    ( (This)->lpVtbl -> get_PrintConfig(This,Value) ) 

#define IPDFReader_put_PrintConfig(This,Value)	\
    ( (This)->lpVtbl -> put_PrintConfig(This,Value) ) 

#define IPDFReader_get_WaterMarkVisible(This,Value)	\
    ( (This)->lpVtbl -> get_WaterMarkVisible(This,Value) ) 

#define IPDFReader_put_WaterMarkVisible(This,Value)	\
    ( (This)->lpVtbl -> put_WaterMarkVisible(This,Value) ) 

#define IPDFReader_CreateSignaturePages(This,SignIndex,SignPass,Pages,mode,Position,Area,Result)	\
    ( (This)->lpVtbl -> CreateSignaturePages(This,SignIndex,SignPass,Pages,mode,Position,Area,Result) ) 

#define IPDFReader_GoToText(This,Text,Page,Case,UpDown,Selected,Result)	\
    ( (This)->lpVtbl -> GoToText(This,Text,Page,Case,UpDown,Selected,Result) ) 

#define IPDFReader_IsPagesSigned(This,Pages,SignType,Result)	\
    ( (This)->lpVtbl -> IsPagesSigned(This,Pages,SignType,Result) ) 

#define IPDFReader_OpenStream(This,AStream,Result)	\
    ( (This)->lpVtbl -> OpenStream(This,AStream,Result) ) 

#define IPDFReader_SaveStream(This,AStream,Result)	\
    ( (This)->lpVtbl -> SaveStream(This,AStream,Result) ) 

#define IPDFReader_SetUserPassWord(This,Password,Result)	\
    ( (This)->lpVtbl -> SetUserPassWord(This,Password,Result) ) 

#define IPDFReader_get_DBSignType(This,Value)	\
    ( (This)->lpVtbl -> get_DBSignType(This,Value) ) 

#define IPDFReader_put_DBSignType(This,Value)	\
    ( (This)->lpVtbl -> put_DBSignType(This,Value) ) 

#define IPDFReader_InsertImageByCursorExt(This,Image,isURL,isTrans,actWidth,actHeight,Result)	\
    ( (This)->lpVtbl -> InsertImageByCursorExt(This,Image,isURL,isTrans,actWidth,actHeight,Result) ) 

#define IPDFReader_GetDocumentID(This,Result)	\
    ( (This)->lpVtbl -> GetDocumentID(This,Result) ) 

#define IPDFReader_get_ServerURL(This,Value)	\
    ( (This)->lpVtbl -> get_ServerURL(This,Value) ) 

#define IPDFReader_put_ServerURL(This,Value)	\
    ( (This)->lpVtbl -> put_ServerURL(This,Value) ) 

#define IPDFReader_SetPublicInfo(This,type,Value,Result)	\
    ( (This)->lpVtbl -> SetPublicInfo(This,type,Value,Result) ) 

#define IPDFReader_GetPublicInfo(This,type,Result)	\
    ( (This)->lpVtbl -> GetPublicInfo(This,type,Result) ) 

#define IPDFReader_get_CUSTOMPARAMS(This,Value)	\
    ( (This)->lpVtbl -> get_CUSTOMPARAMS(This,Value) ) 

#define IPDFReader_put_CUSTOMPARAMS(This,Value)	\
    ( (This)->lpVtbl -> put_CUSTOMPARAMS(This,Value) ) 

#define IPDFReader_GetTextPosition(This,PageNo,Text,Case,PType,sInfo)	\
    ( (This)->lpVtbl -> GetTextPosition(This,PageNo,Text,Case,PType,sInfo) ) 

#define IPDFReader_GetAnnotTextFile(This,sFileName)	\
    ( (This)->lpVtbl -> GetAnnotTextFile(This,sFileName) ) 

#define IPDFReader_DeletePagesExt(This,Start,Trail,Result)	\
    ( (This)->lpVtbl -> DeletePagesExt(This,Start,Trail,Result) ) 

#define IPDFReader_GetAnnotString(This,sInfo)	\
    ( (This)->lpVtbl -> GetAnnotString(This,sInfo) ) 

#define IPDFReader_AddCommentExt(This,PageNo,X,Y,Text,CTime,MTime,UName,UId,TId,Result)	\
    ( (This)->lpVtbl -> AddCommentExt(This,PageNo,X,Y,Text,CTime,MTime,UName,UId,TId,Result) ) 

#define IPDFReader_StartRect(This,Result)	\
    ( (This)->lpVtbl -> StartRect(This,Result) ) 

#define IPDFReader_GetRectInfo(This,sInfo)	\
    ( (This)->lpVtbl -> GetRectInfo(This,sInfo) ) 

#define IPDFReader_InsertImageByString(This,PageNo,X,Y,CTime,MTime,UName,UId,strPic,Width,Height,PId,Result)	\
    ( (This)->lpVtbl -> InsertImageByString(This,PageNo,X,Y,CTime,MTime,UName,UId,strPic,Width,Height,PId,Result) ) 

#define IPDFReader_SetPostilPenColor(This,Result)	\
    ( (This)->lpVtbl -> SetPostilPenColor(This,Result) ) 

#define IPDFReader_SetPostilPenWidth(This,pWidth,Result)	\
    ( (This)->lpVtbl -> SetPostilPenWidth(This,pWidth,Result) ) 

#define IPDFReader_CancelPostil(This,Result)	\
    ( (This)->lpVtbl -> CancelPostil(This,Result) ) 

#define IPDFReader_DrawRect(This,PageNo,X1,Y1,X2,Y2,Result)	\
    ( (This)->lpVtbl -> DrawRect(This,PageNo,X1,Y1,X2,Y2,Result) ) 

#define IPDFReader_GetFieldNames(This,strNames)	\
    ( (This)->lpVtbl -> GetFieldNames(This,strNames) ) 

#define IPDFReader_GetBookMarks(This,strBookMarks)	\
    ( (This)->lpVtbl -> GetBookMarks(This,strBookMarks) ) 

#define IPDFReader_GoToAnnot(This,strID,Result)	\
    ( (This)->lpVtbl -> GoToAnnot(This,strID,Result) ) 

#define IPDFReader_GetCPUID(This,Result)	\
    ( (This)->lpVtbl -> GetCPUID(This,Result) ) 

#define IPDFReader_GetHarDiskID(This,strResult)	\
    ( (This)->lpVtbl -> GetHarDiskID(This,strResult) ) 

#define IPDFReader_get_IsLocalPrint(This,Value)	\
    ( (This)->lpVtbl -> get_IsLocalPrint(This,Value) ) 

#define IPDFReader_put_IsLocalPrint(This,Value)	\
    ( (This)->lpVtbl -> put_IsLocalPrint(This,Value) ) 

#define IPDFReader_InsertImageByPositionExt(This,strLocationInfo,mode,nStartPage,nEndPage,Width,Height,strImagePath,isURL,TranPre,lResult)	\
    ( (This)->lpVtbl -> InsertImageByPositionExt(This,strLocationInfo,mode,nStartPage,nEndPage,Width,Height,strImagePath,isURL,TranPre,lResult) ) 

#define IPDFReader_CreateSignatureByImageExt(This,imageFile,SignPass,bProtected,nStartPageNo,nEndPageNo,mode,Position,TranPre,lResult)	\
    ( (This)->lpVtbl -> CreateSignatureByImageExt(This,imageFile,SignPass,bProtected,nStartPageNo,nEndPageNo,mode,Position,TranPre,lResult) ) 

#define IPDFReader_MakeDocOWP(This,OWP,lResult)	\
    ( (This)->lpVtbl -> MakeDocOWP(This,OWP,lResult) ) 

#define IPDFReader_CommentWindow(This,AllOpen,lResult)	\
    ( (This)->lpVtbl -> CommentWindow(This,AllOpen,lResult) ) 

#define IPDFReader_CreateBarCodeImage(This,BarCode,StartPage,EndPage,mode,Pos,nType,lResult)	\
    ( (This)->lpVtbl -> CreateBarCodeImage(This,BarCode,StartPage,EndPage,mode,Pos,nType,lResult) ) 

#define IPDFReader_FileSize(This,lResult)	\
    ( (This)->lpVtbl -> FileSize(This,lResult) ) 

#define IPDFReader_SeriesSignatureExt(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,ZoomPercent,rDegree,Result)	\
    ( (This)->lpVtbl -> SeriesSignatureExt(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,ZoomPercent,rDegree,Result) ) 

#define IPDFReader_SaveLocalFileNoSignature(This,FileName,bResult)	\
    ( (This)->lpVtbl -> SaveLocalFileNoSignature(This,FileName,bResult) ) 

#define IPDFReader_InsertImageExt(This,PageNo,X,Y,Width,Height,Image,Tback,dTran,Rotate,Result)	\
    ( (This)->lpVtbl -> InsertImageExt(This,PageNo,X,Y,Width,Height,Image,Tback,dTran,Rotate,Result) ) 

#define IPDFReader_GetTextPositionAll(This,strText,strFileName,strInf)	\
    ( (This)->lpVtbl -> GetTextPositionAll(This,strText,strFileName,strInf) ) 

#define IPDFReader_CreateSignatureByString(This,strInput,nPage,Pos,FName,FSize,RColor,GColor,BColor,mode,lResult)	\
    ( (This)->lpVtbl -> CreateSignatureByString(This,strInput,nPage,Pos,FName,FSize,RColor,GColor,BColor,mode,lResult) ) 

#define IPDFReader_get_AnnotCoordinate(This,Value)	\
    ( (This)->lpVtbl -> get_AnnotCoordinate(This,Value) ) 

#define IPDFReader_get_TSServerUrl(This,Value)	\
    ( (This)->lpVtbl -> get_TSServerUrl(This,Value) ) 

#define IPDFReader_put_TSServerUrl(This,Value)	\
    ( (This)->lpVtbl -> put_TSServerUrl(This,Value) ) 

#define IPDFReader_put_TSUser(This,rhs)	\
    ( (This)->lpVtbl -> put_TSUser(This,rhs) ) 

#define IPDFReader_put_TSPwd(This,rhs)	\
    ( (This)->lpVtbl -> put_TSPwd(This,rhs) ) 

#define IPDFReader_get_SignSerial(This,Value)	\
    ( (This)->lpVtbl -> get_SignSerial(This,Value) ) 

#define IPDFReader_get_SignSerialEnabled(This,Value)	\
    ( (This)->lpVtbl -> get_SignSerialEnabled(This,Value) ) 

#define IPDFReader_put_SignSerialEnabled(This,Value)	\
    ( (This)->lpVtbl -> put_SignSerialEnabled(This,Value) ) 

#define IPDFReader_ClearImageSignSerial(This)	\
    ( (This)->lpVtbl -> ClearImageSignSerial(This) ) 

#define IPDFReader_AddImageSignSerial(This,fontSize,FontColor,FontName,SignSerial)	\
    ( (This)->lpVtbl -> AddImageSignSerial(This,fontSize,FontColor,FontName,SignSerial) ) 

#define IPDFReader_DrawRectExt(This,PageNo,X1,Y1,X2,Y2,ishighlight,Result)	\
    ( (This)->lpVtbl -> DrawRectExt(This,PageNo,X1,Y1,X2,Y2,ishighlight,Result) ) 

#define IPDFReader_get_CommentTextMoveRight(This,Value)	\
    ( (This)->lpVtbl -> get_CommentTextMoveRight(This,Value) ) 

#define IPDFReader_put_CommentTextMoveRight(This,Value)	\
    ( (This)->lpVtbl -> put_CommentTextMoveRight(This,Value) ) 

#define IPDFReader_GetRealSignature(This,strParam,strResult)	\
    ( (This)->lpVtbl -> GetRealSignature(This,strParam,strResult) ) 

#define IPDFReader_CreateStraddleSignature(This,SignIndex,SignPass,Position,isBialteral,EvenOrOdd,strRate,Area,lResult)	\
    ( (This)->lpVtbl -> CreateStraddleSignature(This,SignIndex,SignPass,Position,isBialteral,EvenOrOdd,strRate,Area,lResult) ) 

#define IPDFReader_SetFieldByName(This,Name,Value,bResult)	\
    ( (This)->lpVtbl -> SetFieldByName(This,Name,Value,bResult) ) 

#define IPDFReader_GetFieldByName(This,Name,strResult)	\
    ( (This)->lpVtbl -> GetFieldByName(This,Name,strResult) ) 

#define IPDFReader_ClearFieldByName(This,bResult)	\
    ( (This)->lpVtbl -> ClearFieldByName(This,bResult) ) 

#define IPDFReader_MergeRealSignature(This,strFileName,strSignInfo,lResult)	\
    ( (This)->lpVtbl -> MergeRealSignature(This,strFileName,strSignInfo,lResult) ) 

#define IPDFReader_SaveFileToBase64(This,type,strResult)	\
    ( (This)->lpVtbl -> SaveFileToBase64(This,type,strResult) ) 

#define IPDFReader_WebOpenBase64(This,bResult)	\
    ( (This)->lpVtbl -> WebOpenBase64(This,bResult) ) 

#define IPDFReader_WebSaveBase64(This,bResult)	\
    ( (This)->lpVtbl -> WebSaveBase64(This,bResult) ) 

#define IPDFReader_get_CustomPdfDocInfo(This,Value)	\
    ( (This)->lpVtbl -> get_CustomPdfDocInfo(This,Value) ) 

#define IPDFReader_put_CustomPdfDocInfo(This,Value)	\
    ( (This)->lpVtbl -> put_CustomPdfDocInfo(This,Value) ) 

#define IPDFReader_WebFastSave(This,bResult)	\
    ( (This)->lpVtbl -> WebFastSave(This,bResult) ) 

#define IPDFReader_get_BufSize(This,Value)	\
    ( (This)->lpVtbl -> get_BufSize(This,Value) ) 

#define IPDFReader_put_BufSize(This,Value)	\
    ( (This)->lpVtbl -> put_BufSize(This,Value) ) 

#define IPDFReader_SignatureCountExt(This,strName,Result)	\
    ( (This)->lpVtbl -> SignatureCountExt(This,strName,Result) ) 

#define IPDFReader_GetSignIfo(This,nSigIndex,strName,sResult)	\
    ( (This)->lpVtbl -> GetSignIfo(This,nSigIndex,strName,sResult) ) 

#define IPDFReader_GetSignaturePos(This,Index,strResult)	\
    ( (This)->lpVtbl -> GetSignaturePos(This,Index,strResult) ) 

#define IPDFReader_FastSeriesSignature(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,ReferencePoint,Result)	\
    ( (This)->lpVtbl -> FastSeriesSignature(This,StartPageNo,EndPageNo,Index,Pass,mode,Postil,Area,ReferencePoint,Result) ) 

#define IPDFReader_get_isCopyRight(This,Value)	\
    ( (This)->lpVtbl -> get_isCopyRight(This,Value) ) 

#define IPDFReader_get_SelectedBookMarkName(This,Value)	\
    ( (This)->lpVtbl -> get_SelectedBookMarkName(This,Value) ) 

#define IPDFReader_PrintWaterMark(This,strContent,strName,nFSize,nFRColor,nFGColor,nFBColor,nFRotate,lResult)	\
    ( (This)->lpVtbl -> PrintWaterMark(This,strContent,strName,nFSize,nFRColor,nFGColor,nFBColor,nFRotate,lResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_CopyRight_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR rhs);


void __RPC_STUB IPDFReader_put_CopyRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_Binary_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT *Value);


void __RPC_STUB IPDFReader_get_Binary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_Binary_Proxy( 
    IPDFReader * This,
    /* [in] */ VARIANT Value);


void __RPC_STUB IPDFReader_put_Binary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ImportPages_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FileName,
    /* [in] */ long Start,
    /* [in] */ long Trail,
    /* [in] */ long Place,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_ImportPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DeletePages_Proxy( 
    IPDFReader * This,
    /* [in] */ long Start,
    /* [in] */ long Trail,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_DeletePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SearchText_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Text,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_SearchText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ExtParam1_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_ExtParam1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ExtParam1_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_ExtParam1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ExtParam2_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_ExtParam2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ExtParam2_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_ExtParam2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ThirdTime_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_ThirdTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ThirdTime_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_ThirdTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignatureFileName_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_SignatureFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_SignatureFileName_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_SignatureFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GrayDocument_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR ExParam,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GrayDocument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ImportFieldValue_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FieldName,
    /* [in] */ BSTR FieldValue,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_ImportFieldValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ExportFieldValue_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FieldName,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_ExportFieldValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ImportImagePage_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FileName,
    /* [in] */ long Zoom,
    /* [in] */ long isMapping,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_ImportImagePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ImportTemplate_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR XML,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_ImportTemplate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebSaveAccessory_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *bResult);


void __RPC_STUB IPDFReader_WebSaveAccessory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_FullScreen_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_FullScreen_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GotoPreviousScreen_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GotoPreviousScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GotoNextScreen_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GotoNextScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GotoViewSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long Index,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GotoViewSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CancelSignature_Proxy( 
    IPDFReader * This);


void __RPC_STUB IPDFReader_CancelSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebSaveLocalFileEx_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FileName,
    /* [in] */ BSTR Password,
    /* [in] */ BSTR LocalPath,
    /* [in] */ BSTR Ext1,
    /* [in] */ BSTR Ext2,
    /* [in] */ BSTR Ext3,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_WebSaveLocalFileEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebOpenLocalFileEx_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FileName,
    /* [in] */ BSTR Password,
    /* [in] */ BSTR LocalPath,
    /* [in] */ BSTR Ext1,
    /* [in] */ BSTR Ext2,
    /* [in] */ BSTR Ext3,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_WebOpenLocalFileEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebGetMAC_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_WebGetMAC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebGetIP_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_WebGetIP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_HandWriter_Proxy( 
    IPDFReader * This,
    /* [in] */ long type,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_HandWriter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_EnableHandWriter_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_EnableHandWriter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_EnableHandWriter_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_EnableHandWriter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImage_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X,
    /* [in] */ float Y,
    /* [in] */ float Width,
    /* [in] */ float Height,
    /* [in] */ BSTR Image,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertText_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X,
    /* [in] */ float Y,
    /* [in] */ BSTR Text,
    /* [in] */ long fontSize,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageByCursor_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Image,
    /* [in] */ long isURL,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertImageByCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_LockScreen_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_LockScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_UnlockScreen_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_UnlockScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetCoordinate_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SetCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetCoordinate_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_GetCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SeriesSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long StartPageNo,
    /* [in] */ long EndPageNo,
    /* [in] */ long Index,
    /* [in] */ BSTR Pass,
    /* [in] */ long mode,
    /* [in] */ BSTR Postil,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SeriesSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ShowSearchDlg_Proxy( 
    IPDFReader * This);


void __RPC_STUB IPDFReader_ShowSearchDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ShowSchedule_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ShowSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ShowSchedule_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ShowSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_AllowSignName_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_AllowSignName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_AllowSignName_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_AllowSignName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DeleteUserTools_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Index);


void __RPC_STUB IPDFReader_DeleteUserTools_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DeleteUserMenus_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Index);


void __RPC_STUB IPDFReader_DeleteUserMenus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AddComment_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ BSTR Text,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_AddComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ShowPostil_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ShowPostil_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ShowPostil_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ShowPostil_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_FastSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long SignIndex,
    /* [in] */ BSTR SignPass,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_FastSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_AllowMoveAnnot_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_AllowMoveAnnot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_AllowMoveAnnot_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_AllowMoveAnnot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebInsertImage_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value,
    /* [in] */ long PageNo,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_WebInsertImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ImportFieldValueByXML_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR sXML,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_ImportFieldValueByXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_EnableUpdating_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT_BOOL *Value);


void __RPC_STUB IPDFReader_get_EnableUpdating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_EnableUpdating_Proxy( 
    IPDFReader * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IPDFReader_put_EnableUpdating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebSetScrollBarPos_Proxy( 
    IPDFReader * This,
    /* [in] */ long xPos,
    /* [in] */ long yPos,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_WebSetScrollBarPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebGetKeySN_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_WebGetKeySN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageByPosition_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR sName,
    /* [in] */ long mode,
    /* [in] */ long nStartPage,
    /* [in] */ long nEndPage,
    /* [in] */ float Width,
    /* [in] */ float Height,
    /* [in] */ BSTR sImagePath,
    /* [in] */ long isURL,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_InsertImageByPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebPrintEx_Proxy( 
    IPDFReader * This,
    /* [in] */ long Copies,
    /* [in] */ BSTR PrinterName,
    /* [in] */ BSTR PageArea,
    /* [in] */ VARIANT_BOOL ShowDlg,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_WebPrintEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetTextPostilInfo_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *sResult);


void __RPC_STUB IPDFReader_GetTextPostilInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_DocumentModified_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_DocumentModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_TextCommentRight_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_TextCommentRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_TextCommentRight_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_TextCommentRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CheckPdfHasSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR filePath,
    /* [retval][out] */ BSTR *lResult);


void __RPC_STUB IPDFReader_CheckPdfHasSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ShowPostilList_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ShowPostilList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ShowPostilList_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ShowPostilList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetSelectState_Proxy( 
    IPDFReader * This,
    /* [in] */ long state,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_SetSelectState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebDoffSealToImage_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_WebDoffSealToImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_LocalPrinterNameList_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_LocalPrinterNameList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_LocalPrinterDriverList_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_LocalPrinterDriverList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebImageToPDF_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR sImagePath,
    /* [in] */ BSTR sPdfPath,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_WebImageToPDF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebPrintControl_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR PrinterName,
    /* [in] */ long MaxPrintCopies,
    /* [in] */ long PrintCopies,
    /* [in] */ BSTR PrintPage,
    /* [in] */ long ShowDlg,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_WebPrintControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignatureOutputFlags_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_SignatureOutputFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_SignatureOutputFlags_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_SignatureOutputFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_EnabledHideKeywords_Proxy( 
    IPDFReader * This,
    /* [in] */ long Ch,
    /* [in] */ VARIANT_BOOL Value,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_EnabledHideKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AppendHideKeywords_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Keywords);


void __RPC_STUB IPDFReader_AppendHideKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SaveSignDataToLocal_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *lRet);


void __RPC_STUB IPDFReader_SaveSignDataToLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_LoadLocalSignData_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strSignData,
    /* [retval][out] */ long *lRet);


void __RPC_STUB IPDFReader_LoadLocalSignData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_UserID_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_UserID_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_UserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignatureMode_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_SignatureMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_SignatureMode_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_SignatureMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateBarcodeSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR barcodeString,
    /* [in] */ long bShowDlg,
    /* [in] */ BSTR SignPass,
    /* [in] */ long lStartPage,
    /* [in] */ long lEndPage,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *lRet);


void __RPC_STUB IPDFReader_CreateBarcodeSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ShowDigitalSignature_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ShowDigitalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ShowDigitalSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ShowDigitalSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AppendRevision_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Revision);


void __RPC_STUB IPDFReader_AppendRevision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ClearRevisions_Proxy( 
    IPDFReader * This);


void __RPC_STUB IPDFReader_ClearRevisions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetCurrentRevision_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR CustomData,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_GetCurrentRevision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_RevisionCount_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_RevisionCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetRevisionCustomData_Proxy( 
    IPDFReader * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR *sRet);


void __RPC_STUB IPDFReader_GetRevisionCustomData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetCryptPassword_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR pwd,
    /* [retval][out] */ VARIANT_BOOL *lRet);


void __RPC_STUB IPDFReader_SetCryptPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AddImageText_Proxy( 
    IPDFReader * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ long fontSize,
    /* [in] */ long FontColor,
    /* [in] */ BSTR FontName,
    /* [in] */ BSTR Text);


void __RPC_STUB IPDFReader_AddImageText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ClearImageText_Proxy( 
    IPDFReader * This);


void __RPC_STUB IPDFReader_ClearImageText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ImageTextEnabled_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT_BOOL *Value);


void __RPC_STUB IPDFReader_get_ImageTextEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ImageTextEnabled_Proxy( 
    IPDFReader * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IPDFReader_put_ImageTextEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebAddBookmark_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strValue,
    /* [retval][out] */ VARIANT_BOOL *lResult);


void __RPC_STUB IPDFReader_WebAddBookmark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebDelBookmark_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strValue,
    /* [retval][out] */ VARIANT_BOOL *lResult);


void __RPC_STUB IPDFReader_WebDelBookmark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebGetFilePath_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_WebGetFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateSignatureByName_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR sealName,
    /* [in] */ long StartPageNo,
    /* [in] */ long EndPageNo,
    /* [in] */ BSTR Password,
    /* [in] */ long mode,
    /* [in] */ BSTR posText,
    /* [in] */ BSTR protectArea,
    /* [retval][out] */ long *lRet);


void __RPC_STUB IPDFReader_CreateSignatureByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateRayCodeSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR SignPass,
    /* [in] */ long PageNo,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_CreateRayCodeSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateQRCodeSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR QRCodeString,
    /* [in] */ long bShowDlg,
    /* [in] */ BSTR SigPass,
    /* [in] */ long lStartPage,
    /* [in] */ long lEndPage,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CreateQRCodeSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_AppCode_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_AppCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_AppCode_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_AppCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_IsPrintControl_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_IsPrintControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_IsPrintControl_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_IsPrintControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ShowToolBarHint_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ShowToolBarHint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ShowToolBarHint_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ShowToolBarHint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertMoveText_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strInput,
    /* [in] */ long nPage,
    /* [in] */ BSTR Pos,
    /* [in] */ BSTR FName,
    /* [in] */ long FSize,
    /* [in] */ long RColor,
    /* [in] */ long GColor,
    /* [in] */ long BColor,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_InsertMoveText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ImageAnnotDelRight_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ImageAnnotDelRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ImageAnnotDelRight_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ImageAnnotDelRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ImageAnnotMoveRight_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_ImageAnnotMoveRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ImageAnnotMoveRight_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_ImageAnnotMoveRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateSignatureByImage_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR imageFile,
    /* [in] */ BSTR SignPass,
    /* [in] */ VARIANT_BOOL bProtected,
    /* [in] */ long nStartPage,
    /* [in] */ long nEndPage,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_CreateSignatureByImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertMoveTextExt_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strInput,
    /* [in] */ long nPage,
    /* [in] */ long mode,
    /* [in] */ BSTR Pos,
    /* [in] */ long PosType,
    /* [in] */ BSTR FName,
    /* [in] */ long FSize,
    /* [in] */ long RColor,
    /* [in] */ long GColor,
    /* [in] */ long BColor,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_InsertMoveTextExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignatureFrom_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_SignatureFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_SignatureFrom_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_SignatureFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_UserRole_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_UserRole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_UserRole_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_UserRole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GoToTextComment_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR TextID,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_GoToTextComment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_FastSignatureByImage_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR imageFile,
    /* [in] */ BSTR SignPass,
    /* [in] */ VARIANT_BOOL bProtected,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_FastSignatureByImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_IsShowInputBox_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_IsShowInputBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_IsShowInputBox_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_IsShowInputBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetSpecificSignCount_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Pages,
    /* [in] */ long SignType,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GetSpecificSignCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_PrintConfig_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_PrintConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_PrintConfig_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_PrintConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_WaterMarkVisible_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_WaterMarkVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_WaterMarkVisible_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_WaterMarkVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateSignaturePages_Proxy( 
    IPDFReader * This,
    /* [in] */ long SignIndex,
    /* [in] */ BSTR SignPass,
    /* [in] */ BSTR Pages,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_CreateSignaturePages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GoToText_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Text,
    /* [in] */ long Page,
    /* [in] */ VARIANT_BOOL Case,
    /* [in] */ VARIANT_BOOL UpDown,
    /* [in] */ VARIANT_BOOL Selected,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GoToText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_IsPagesSigned_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Pages,
    /* [in] */ long SignType,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_IsPagesSigned_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_OpenStream_Proxy( 
    IPDFReader * This,
    /* [in] */ VARIANT *AStream,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_OpenStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SaveStream_Proxy( 
    IPDFReader * This,
    /* [out] */ VARIANT *AStream,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SaveStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetUserPassWord_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Password,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SetUserPassWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_DBSignType_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_DBSignType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_DBSignType_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_DBSignType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageByCursorExt_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Image,
    /* [in] */ long isURL,
    /* [in] */ long isTrans,
    /* [in] */ long actWidth,
    /* [in] */ long actHeight,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertImageByCursorExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetDocumentID_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_GetDocumentID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_ServerURL_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_ServerURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_ServerURL_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_ServerURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetPublicInfo_Proxy( 
    IPDFReader * This,
    /* [in] */ long type,
    /* [in] */ BSTR Value,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SetPublicInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetPublicInfo_Proxy( 
    IPDFReader * This,
    /* [in] */ long type,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_GetPublicInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_CUSTOMPARAMS_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_CUSTOMPARAMS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_CUSTOMPARAMS_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_CUSTOMPARAMS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetTextPosition_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ BSTR Text,
    /* [in] */ VARIANT_BOOL Case,
    /* [in] */ long PType,
    /* [retval][out] */ BSTR *sInfo);


void __RPC_STUB IPDFReader_GetTextPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetAnnotTextFile_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *sFileName);


void __RPC_STUB IPDFReader_GetAnnotTextFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DeletePagesExt_Proxy( 
    IPDFReader * This,
    /* [in] */ long Start,
    /* [in] */ long Trail,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_DeletePagesExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetAnnotString_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *sInfo);


void __RPC_STUB IPDFReader_GetAnnotString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AddCommentExt_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X,
    /* [in] */ float Y,
    /* [in] */ BSTR Text,
    /* [in] */ BSTR CTime,
    /* [in] */ BSTR MTime,
    /* [in] */ BSTR UName,
    /* [in] */ BSTR UId,
    /* [in] */ BSTR TId,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_AddCommentExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_StartRect_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_StartRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetRectInfo_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *sInfo);


void __RPC_STUB IPDFReader_GetRectInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageByString_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X,
    /* [in] */ float Y,
    /* [in] */ BSTR CTime,
    /* [in] */ BSTR MTime,
    /* [in] */ BSTR UName,
    /* [in] */ BSTR UId,
    /* [in] */ BSTR strPic,
    /* [in] */ float Width,
    /* [in] */ float Height,
    /* [in] */ BSTR PId,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertImageByString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetPostilPenColor_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SetPostilPenColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetPostilPenWidth_Proxy( 
    IPDFReader * This,
    /* [in] */ long pWidth,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SetPostilPenWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CancelPostil_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT_BOOL *Result);


void __RPC_STUB IPDFReader_CancelPostil_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DrawRect_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X1,
    /* [in] */ float Y1,
    /* [in] */ float X2,
    /* [in] */ float Y2,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_DrawRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetFieldNames_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *strNames);


void __RPC_STUB IPDFReader_GetFieldNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetBookMarks_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *strBookMarks);


void __RPC_STUB IPDFReader_GetBookMarks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GoToAnnot_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strID,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_GoToAnnot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetCPUID_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IPDFReader_GetCPUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetHarDiskID_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *strResult);


void __RPC_STUB IPDFReader_GetHarDiskID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_IsLocalPrint_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_IsLocalPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_IsLocalPrint_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_IsLocalPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageByPositionExt_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strLocationInfo,
    /* [in] */ long mode,
    /* [in] */ long nStartPage,
    /* [in] */ long nEndPage,
    /* [in] */ float Width,
    /* [in] */ float Height,
    /* [in] */ BSTR strImagePath,
    /* [in] */ long isURL,
    /* [in] */ float TranPre,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_InsertImageByPositionExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateSignatureByImageExt_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR imageFile,
    /* [in] */ BSTR SignPass,
    /* [in] */ VARIANT_BOOL bProtected,
    /* [in] */ long nStartPageNo,
    /* [in] */ long nEndPageNo,
    /* [in] */ long mode,
    /* [in] */ BSTR Position,
    /* [in] */ float TranPre,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CreateSignatureByImageExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_MakeDocOWP_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR OWP,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_MakeDocOWP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CommentWindow_Proxy( 
    IPDFReader * This,
    /* [in] */ int AllOpen,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CommentWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateBarCodeImage_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR BarCode,
    /* [in] */ long StartPage,
    /* [in] */ long EndPage,
    /* [in] */ long mode,
    /* [in] */ BSTR Pos,
    /* [in] */ long nType,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CreateBarCodeImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_FileSize_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_FileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SeriesSignatureExt_Proxy( 
    IPDFReader * This,
    /* [in] */ long StartPageNo,
    /* [in] */ long EndPageNo,
    /* [in] */ long Index,
    /* [in] */ BSTR Pass,
    /* [in] */ long mode,
    /* [in] */ BSTR Postil,
    /* [in] */ BSTR Area,
    /* [in] */ double ZoomPercent,
    /* [in] */ double rDegree,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SeriesSignatureExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SaveLocalFileNoSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR FileName,
    /* [retval][out] */ long *bResult);


void __RPC_STUB IPDFReader_SaveLocalFileNoSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_InsertImageExt_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X,
    /* [in] */ float Y,
    /* [in] */ float Width,
    /* [in] */ float Height,
    /* [in] */ BSTR Image,
    /* [in] */ VARIANT_BOOL Tback,
    /* [in] */ float dTran,
    /* [in] */ float Rotate,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_InsertImageExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetTextPositionAll_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strText,
    /* [in] */ BSTR strFileName,
    /* [retval][out] */ BSTR *strInf);


void __RPC_STUB IPDFReader_GetTextPositionAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateSignatureByString_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strInput,
    /* [in] */ long nPage,
    /* [in] */ BSTR Pos,
    /* [in] */ BSTR FName,
    /* [in] */ long FSize,
    /* [in] */ long RColor,
    /* [in] */ long GColor,
    /* [in] */ long BColor,
    /* [in] */ long mode,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CreateSignatureByString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_AnnotCoordinate_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_AnnotCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_TSServerUrl_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_TSServerUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_TSServerUrl_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_TSServerUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_TSUser_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR rhs);


void __RPC_STUB IPDFReader_put_TSUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_TSPwd_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR rhs);


void __RPC_STUB IPDFReader_put_TSPwd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignSerial_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_SignSerial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SignSerialEnabled_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT_BOOL *Value);


void __RPC_STUB IPDFReader_get_SignSerialEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_SignSerialEnabled_Proxy( 
    IPDFReader * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IPDFReader_put_SignSerialEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ClearImageSignSerial_Proxy( 
    IPDFReader * This);


void __RPC_STUB IPDFReader_ClearImageSignSerial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_AddImageSignSerial_Proxy( 
    IPDFReader * This,
    /* [in] */ long fontSize,
    /* [in] */ long FontColor,
    /* [in] */ BSTR FontName,
    /* [in] */ BSTR SignSerial);


void __RPC_STUB IPDFReader_AddImageSignSerial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_DrawRectExt_Proxy( 
    IPDFReader * This,
    /* [in] */ long PageNo,
    /* [in] */ float X1,
    /* [in] */ float Y1,
    /* [in] */ float X2,
    /* [in] */ float Y2,
    /* [in] */ long ishighlight,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_DrawRectExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_CommentTextMoveRight_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_CommentTextMoveRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_CommentTextMoveRight_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_CommentTextMoveRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetRealSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strParam,
    /* [retval][out] */ BSTR *strResult);


void __RPC_STUB IPDFReader_GetRealSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_CreateStraddleSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long SignIndex,
    /* [in] */ BSTR SignPass,
    /* [in] */ BSTR Position,
    /* [in] */ long isBialteral,
    /* [in] */ long EvenOrOdd,
    /* [in] */ BSTR strRate,
    /* [in] */ BSTR Area,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_CreateStraddleSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SetFieldByName_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Value,
    /* [retval][out] */ VARIANT_BOOL *bResult);


void __RPC_STUB IPDFReader_SetFieldByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetFieldByName_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ BSTR *strResult);


void __RPC_STUB IPDFReader_GetFieldByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_ClearFieldByName_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ VARIANT_BOOL *bResult);


void __RPC_STUB IPDFReader_ClearFieldByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_MergeRealSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strFileName,
    /* [in] */ BSTR strSignInfo,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_MergeRealSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SaveFileToBase64_Proxy( 
    IPDFReader * This,
    /* [in] */ long type,
    /* [retval][out] */ BSTR *strResult);


void __RPC_STUB IPDFReader_SaveFileToBase64_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebOpenBase64_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *bResult);


void __RPC_STUB IPDFReader_WebOpenBase64_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebSaveBase64_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *bResult);


void __RPC_STUB IPDFReader_WebSaveBase64_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_CustomPdfDocInfo_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_CustomPdfDocInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_CustomPdfDocInfo_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR Value);


void __RPC_STUB IPDFReader_put_CustomPdfDocInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_WebFastSave_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *bResult);


void __RPC_STUB IPDFReader_WebFastSave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_BufSize_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_BufSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_put_BufSize_Proxy( 
    IPDFReader * This,
    /* [in] */ long Value);


void __RPC_STUB IPDFReader_put_BufSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_SignatureCountExt_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strName,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_SignatureCountExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetSignIfo_Proxy( 
    IPDFReader * This,
    /* [in] */ long nSigIndex,
    /* [in] */ BSTR strName,
    /* [retval][out] */ BSTR *sResult);


void __RPC_STUB IPDFReader_GetSignIfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_GetSignaturePos_Proxy( 
    IPDFReader * This,
    /* [in] */ long Index,
    /* [retval][out] */ BSTR *strResult);


void __RPC_STUB IPDFReader_GetSignaturePos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_FastSeriesSignature_Proxy( 
    IPDFReader * This,
    /* [in] */ long StartPageNo,
    /* [in] */ long EndPageNo,
    /* [in] */ long Index,
    /* [in] */ BSTR Pass,
    /* [in] */ long mode,
    /* [in] */ BSTR Postil,
    /* [in] */ BSTR Area,
    /* [in] */ long ReferencePoint,
    /* [retval][out] */ long *Result);


void __RPC_STUB IPDFReader_FastSeriesSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_isCopyRight_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ long *Value);


void __RPC_STUB IPDFReader_get_isCopyRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IPDFReader_get_SelectedBookMarkName_Proxy( 
    IPDFReader * This,
    /* [retval][out] */ BSTR *Value);


void __RPC_STUB IPDFReader_get_SelectedBookMarkName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IPDFReader_PrintWaterMark_Proxy( 
    IPDFReader * This,
    /* [in] */ BSTR strContent,
    /* [in] */ BSTR strName,
    /* [in] */ long nFSize,
    /* [in] */ long nFRColor,
    /* [in] */ long nFGColor,
    /* [in] */ long nFBColor,
    /* [in] */ long nFRotate,
    /* [retval][out] */ long *lResult);


void __RPC_STUB IPDFReader_PrintWaterMark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDFReader_INTERFACE_DEFINED__ */


#ifndef __IPDFReaderEvents_DISPINTERFACE_DEFINED__
#define __IPDFReaderEvents_DISPINTERFACE_DEFINED__

/* dispinterface IPDFReaderEvents */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID DIID_IPDFReaderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3ED99097-3032-4374-905F-518738076E29")
    IPDFReaderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IPDFReaderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPDFReaderEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPDFReaderEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPDFReaderEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPDFReaderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPDFReaderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPDFReaderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPDFReaderEvents * This,
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
    } IPDFReaderEventsVtbl;

    interface IPDFReaderEvents
    {
        CONST_VTBL struct IPDFReaderEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDFReaderEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPDFReaderEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPDFReaderEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPDFReaderEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPDFReaderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPDFReaderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPDFReaderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IPDFReaderEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PDFReader;

#ifdef __cplusplus

class DECLSPEC_UUID("39E08D82-C8AC-4934-BE07-F6E816FD47A1")
PDFReader;
#endif
#endif /* __iWebPDF_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


