//------------------------------------------------------------------------------
//
// File Name:	Component.cpp
// Author(s):	Bar Ben-zvi
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Component.h"
#include "GameObject.h"


Component::Component(const std::string& name)
	: BetaObject(name)
{
}

GameObject* Component::GetOwner() const
{
	return static_cast<GameObject*>(GetParent());
}
