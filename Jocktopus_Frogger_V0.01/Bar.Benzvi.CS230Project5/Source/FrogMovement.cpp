//------------------------------------------------------------------------------
//
// File Name:	FrogMovement.cpp
// Author(s):	Freddy Martin
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "FrogMovement.h"
#include <Sprite.h>
#include <Parser.h>
#include <Collider.h>
#include <GameObject.h>
#include <Space.h>
#include <Input.h>
#include <Transform.h>

namespace Behaviors
{
	FrogMovement::FrogMovement(float speed)
		:Component("FrogMovement"), speed(speed), canWalk(true)
	{
	}
	Component * FrogMovement::Clone() const
	{
		return new FrogMovement(*this);
	}
	void FrogMovement::Initialize()
	{
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(FrogCollisionHandler);
	}
	void FrogMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		Input& input = Input::GetInstance();

		if (!canWalk)
		{
			GetOwner()->GetComponent<Sprite>()->SetFrame(0);
			canWalk = true;
		}
		else
		{
			if (input.CheckTriggered('W'))
			{
				GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(0, speed));
				GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI / 2.0f);
				GetOwner()->GetComponent<Sprite>()->SetFrame(1);
			}
			if (input.CheckTriggered('S'))
			{
				GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(0, speed));
				GetOwner()->GetComponent<Transform>()->SetRotation(-(float)M_PI / 2.0f);
				GetOwner()->GetComponent<Sprite>()->SetFrame(1);
			}
			if (input.CheckTriggered('D'))
			{
				GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(speed, 0));
				GetOwner()->GetComponent<Transform>()->SetRotation(0);
				GetOwner()->GetComponent<Sprite>()->SetFrame(1);
			}
			if (input.CheckTriggered('A'))
			{
				GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(speed, 0));
				GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI);
				GetOwner()->GetComponent<Sprite>()->SetFrame(1);
			}
		}
	}
	void FrogMovement::Deserialize(Parser & parser)
	{
		parser.ReadVariable("speed", speed);
	}
	void FrogMovement::Serialize(Parser & parser) const
	{
		parser.WriteVariable("speed", speed);
	}
	void FrogCollisionHandler(GameObject & object, GameObject & other)
	{
		if (other.GetName() == "Car")
		{
			object.GetSpace()->RestartLevel();
		}
	}
}