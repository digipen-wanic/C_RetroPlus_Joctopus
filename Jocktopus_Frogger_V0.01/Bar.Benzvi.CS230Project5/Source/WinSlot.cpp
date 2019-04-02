//------------------------------------------------------------------------------
//
// File Name:	WinSlot.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
// Brief:		Header file for the WinSlot class
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "WinSlot.h"

namespace Behaviors
{
	WinSlot::WinSlot()
		: Component("WinSlot"), containsFrog(false)
	{
	}

	Component* WinSlot::Clone() const
	{
		return new WinSlot(*this);
	}

	bool WinSlot::GetContainsFrog() const
	{
		return containsFrog;
	}

	void WinSlot::SetContainsFrog(bool newContainsFrog)
	{
		containsFrog = newContainsFrog;
	}
}