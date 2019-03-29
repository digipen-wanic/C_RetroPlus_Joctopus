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
#include <Animation.h>

namespace Behaviors
{
	FrogMovement::FrogMovement(float speed, int walkFrames, float deathTime)
		:Component("FrogMovement"), speed(speed), canWalk(0), walkFrames(walkFrames), dying(false), furthestForward(0),
		currentForward(0), onFloat(false), deathTime(deathTime), timer(0)
	{
	}
	Component * FrogMovement::Clone() const
	{
		return new FrogMovement(*this);
	}
	void FrogMovement::Initialize()
	{
		// Init collision handler
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(FrogCollisionHandler);
	}
	void FrogMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		Input& input = Input::GetInstance();

		// Kills the player if they are far enough forward for water and not on a float
		if (currentForward > 6 && !onFloat)
		{
			InitDeathSequence();
		}

		// Runs movement if the player isn't dying
		if (!dying)
		{
			if (canWalk > 0)
			{
				canWalk--;
				if (canWalk <= 0)
				{
					GetOwner()->GetComponent<Sprite>()->SetFrame(0);
				}
			}
			else
			{
				if (input.CheckTriggered('W'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(0, speed));
					GetOwner()->GetComponent<Transform>()->SetRotation(0);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
					currentForward++;
				}
				// If the player isn't at the bottom and s is pressed, move down
				if (currentForward > 0 && input.CheckTriggered('S'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(0, speed));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
					// If currentForward - 1 is less than 0, make it 0, otherwise just subtract 1
					currentForward = (currentForward - 1 < 0) ? 0 : (currentForward - 1);
				}
				if (input.CheckTriggered('D'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(speed, 0));
					GetOwner()->GetComponent<Transform>()->SetRotation(-(float)M_PI / 2.0f);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
				}
				if (input.CheckTriggered('A'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(speed, 0));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI / 2.0f);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
				}
			}
		}
		else
		{
			timer += dt;
			if (timer >= deathTime)
			{
				GetOwner()->GetSpace()->RestartLevel();
			}
		}

		// Checks if the player has moved further forward than before and sets the furthest forward if they have
		if (currentForward > furthestForward)
		{
			furthestForward = currentForward;
		}
	}
	void FrogMovement::Shutdown()
	{
		delete deathAnimation;
	}
	void FrogMovement::Deserialize(Parser & parser)
	{
		parser.ReadVariable("speed", speed);
	}
	void FrogMovement::Serialize(Parser & parser) const
	{
		parser.WriteVariable("speed", speed);
	}
	void FrogMovement::InitDeathSequence()
	{
		if (!dying)
		{
			dying = true;
			GetOwner()->GetComponent<Sprite>()->SetSpriteSource(deathAnimation);
			GetOwner()->GetComponent<Animation>()->Play(0, 4, 0.5f, false);
		}
	}
	void FrogMovement::SetDeathAnimation(SpriteSource * animation)
	{
		delete deathAnimation;
		deathAnimation = animation;
	}
	void FrogCollisionHandler(GameObject & object, GameObject & other)
	{
		if (other.GetName() == "Car")
		{
			object.GetComponent<FrogMovement>()->InitDeathSequence();
		}
		else if (other.GetName() == "Float")
		{
			object.GetComponent<FrogMovement>()->onFloat = true;
		}
	}
}