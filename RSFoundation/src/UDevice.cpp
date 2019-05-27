//
// UDevice.cpp
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "UDevice.h"
#include "SoFProvider.h"
#include "Poco/Exception.h"

using namespace Reach;

UDevice::UDevice()
	:bOpened(false)
{
	open();
}

UDevice::~UDevice()
{
	close();
}

void UDevice::open()
{
	if (bOpened) return;

	if (success != SOF_OpenDevice())
		throw Poco::LogicException("UDevice open failed!", 0x32);
	bOpened = true;
}

void UDevice::close()
{
	if (!bOpened) return;

	if (success != SOF_CloseDevice())
		throw Poco::LogicException("UDevice close failed!", 0x33);
	bOpened = false;
}

bool UDevice::isopen()
{
	return bOpened;
}