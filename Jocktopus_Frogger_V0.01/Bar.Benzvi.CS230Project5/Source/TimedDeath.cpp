//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.cpp
// Author(s):	Bar Ben-zvi
// Project:		CS230 Lab 2: Archetypes and Serialization
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "TimedDeath.h"
#include "GameObject.h"
#include "Parser.h"


namespace Behaviors
{


	TimedDeath::TimedDeath(float timeUntilDeath)
		: Component("TimedDeath"), timeUntilDeath(timeUntilDeath)
	{
	}


	Component* TimedDeath::Clone() const
	{
		return new TimedDeath(*this);
	}

	void TimedDeath::Update(float dt)
	{
		timeUntilDeath -= dt;

		if (timeUntilDeath <= 0)
		{
			GetOwner()->Destroy();
		}
	}

	// Loads object data from a file.
	void TimedDeath::Deserialize(Parser& parser)
	{
		parser.ReadVariable("timeUntilDeath", timeUntilDeath);
	}

	// Saves object data to a file.
	void TimedDeath::Serialize(Parser& parser) const
	{
		parser.WriteVariable("timeUntilDeath", timeUntilDeath);
	}
}