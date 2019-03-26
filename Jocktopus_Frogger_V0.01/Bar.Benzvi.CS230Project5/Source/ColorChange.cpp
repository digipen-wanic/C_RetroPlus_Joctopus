//------------------------------------------------------------------------------
//
// File Name:	ColorChange.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "ColorChange.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Collider.h"
#include "Parser.h"

namespace Behaviors
{
	ColorChange::ColorChange(const Color& normalColor, const Color& collidedColor, float collidedColorTime)
		: Component("ColorChange"), normalColor(normalColor), collidedColor(collidedColor), collidedColorTime(collidedColorTime), collided(false), timer(collidedColorTime)
	{
	}

	Component* ColorChange::Clone() const
	{
		return new ColorChange(*this);
	}

	void ColorChangeCollisionHandler(GameObject& object, GameObject& other)
	{
		UNREFERENCED_PARAMETER(other);

		static_cast<ColorChange*>(object.GetComponent("ColorChange"))->collided = true;
		static_cast<ColorChange*>(object.GetComponent("ColorChange"))->timer = static_cast<ColorChange*>(object.GetComponent("ColorChange"))->collidedColorTime;
	}

	void ColorChange::Initialize()
	{
		sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(&ColorChangeCollisionHandler);
	}

	void ColorChange::Update(float dt)
	{
		if (collided)
		{
			sprite->SetColor(collidedColor);
			collided = false;
		}
		else
		{
			timer -= dt;
			if (timer <= 0.0f)
			{
				sprite->SetColor(normalColor);
			}
		}
	}

	


	// Loads object data from a file.
	void ColorChange::Deserialize(Parser& parser)
	{
		parser.ReadVariable("normalColor", normalColor);
		parser.ReadVariable("collidedColor", collidedColor);
		parser.ReadVariable("colliderColorTime", collidedColorTime);
	}

	// Saves object data to a file.
	void ColorChange::Serialize(Parser& parser) const
	{
		parser.WriteVariable("normalColor", normalColor);
		parser.WriteVariable("collidedColor", collidedColor);
		parser.WriteVariable("colliderColorTime", collidedColorTime);
	}

}