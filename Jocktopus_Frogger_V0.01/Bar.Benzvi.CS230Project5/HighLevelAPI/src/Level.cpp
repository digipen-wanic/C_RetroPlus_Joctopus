//------------------------------------------------------------------------------
//
// File Name:	Level.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Level.h"
#include "Space.h"


Level::Level(const std::string& name)
	: BetaObject(name)
{

}

Space* Level::GetSpace() const
{
	return static_cast<Space*>(GetParent());
}