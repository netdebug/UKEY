//
// SOF.h
//
// Library: Data/SOF
// Package: SOF
// Module:  SOF
//
// Basic definitions for the Poco SOF library.
// This file must be the first file included by every other SOF
// header file.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef SOF_SOF_INCLUDED
#define SOF_SOF_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SOF_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SOF_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(SOF_EXPORTS)
		#define SOF_API __declspec(dllexport)
	#else
		#define SOF_API __declspec(dllimport)
	#endif
#endif


#if !defined(SOF_API)
	#if !defined(POCO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define SOF_API __attribute__ ((visibility ("default")))
	#else
		#define SOF_API
	#endif
#endif


//
// Automatically link SOF library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(SOF_EXPORTS)
		#pragma comment(lib, "rsyncSOF" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // SOF_SOF_INCLUDED
