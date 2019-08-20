//
// FJCA.h
//
// Library: Data/FJCA
// Package: FJCA
// Module:  FJCA
//
// Basic definitions for the Poco FJCA library.
// This file must be the first file included by every other FJCA
// header file.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef FJCA_FJCA_INCLUDED
#define FJCA_FJCA_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FJCA_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FJCA_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(FJCA_EXPORTS)
		#define FJCA_API __declspec(dllexport)
	#else
		#define FJCA_API __declspec(dllimport)
	#endif
#endif


#if !defined(FJCA_API)
	#if !defined(POCO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define FJCA_API __attribute__ ((visibility ("default")))
	#else
		#define FJCA_API
	#endif
#endif


//
// Automatically link FJCA library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(FJCA_EXPORTS)
		#pragma comment(lib, "rsyncFJCA" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // FJCA_FJCA_INCLUDED
