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
#include "ItemMovement.h"
#include <Sprite.h>
#include <Parser.h>
#include <Collider.h>
#include <GameObject.h>
#include <Space.h>
#include <Input.h>
#include <Transform.h>
#include <Animation.h>
#include <Physics.h>
#include "SoundManager.h"
#include "Engine.h"

namespace Behaviors
{
	int FrogMovement::score = 0;
	int FrogMovement::furthestForward = 0;

	FrogMovement::FrogMovement(float speed, int walkFrames, float deathTime)
		:Component("FrogMovement"), speed(speed), canWalk(0), walkFrames(walkFrames), dying(false), 
		currentForward(0), onFloat(false), deathTime(deathTime), timer(0)
	{
	}

	Component * FrogMovement::Clone() const
	{
		return new FrogMovement(*this);
	}

	void FrogCollisionHandler(GameObject& object, GameObject& other)
	{
		if (other.GetName() == "Car")
		{
			object.GetComponent<FrogMovement>()->InitDeathSequence();
		}
		else if (other.GetName() == "Float")
		{
			object.GetComponent<FrogMovement>()->onFloat = true;
			object.GetComponent<Physics>()->SetVelocity(Vector2D(other.GetComponent<ItemMovement>()->GetSpeed() * other.GetComponent<ItemMovement>()->GetDirection(), 0));
		}
	}

	void FrogMovement::Initialize()
	{
		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->AddEffect("Jump.wav");

		// Init collision handler
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(FrogCollisionHandler);
	}

	void FrogMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		Input& input = Input::GetInstance();

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

					soundManager->PlaySound("Jump.wav");

					// Checks if the player has moved further forward than before and sets the furthest forward if they have
					if (currentForward > furthestForward)
					{
						score += (currentForward - furthestForward) * 10;
						furthestForward = currentForward;
					}
				}
				// If the player isn't at the bottom and s is pressed, move down
				if (currentForward > 0 && input.CheckTriggered('S'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(0, speed));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
					// If currentForward - 1 is greater than 0, we can move
					if (currentForward - 1 >= 0)
					{
						currentForward -= 1;
						soundManager->PlaySound("Jump.wav");
					}
					
				}
				if (input.CheckTriggered('D'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(speed, 0));
					GetOwner()->GetComponent<Transform>()->SetRotation(-(float)M_PI / 2.0f);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
					soundManager->PlaySound("Jump.wav");
				}
				if (input.CheckTriggered('A'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(speed, 0));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI / 2.0f);
					GetOwner()->GetComponent<Sprite>()->SetFrame(1);
					canWalk = 2;
					soundManager->PlaySound("Jump.wav");
				}
			}
		}
		else
		{
			timer += dt;
			if (timer >= deathTime)
			{
				GetOwner()->Destroy();
			}
		}
		
	}

	void FrogMovement::FixedUpdate(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// Kills the player if they are far enough forward for water and not on a float
		if (currentForward > 6 && !onFloat)
		{
			InitDeathSequence();
		}

		onFloat = false;
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
			//GetOwner()->GetComponent<Sprite>()->SetSpriteSource(deathAnimation);
			//GetOwner()->GetComponent<Animation>()->Play(0, 4, 0.5f, false);
		}
	}

	void FrogMovement::SetDeathAnimation(SpriteSource * animation)
	{
		delete deathAnimation;
		deathAnimation = animation;
	}

	

	int FrogMovement::GetScore() const
	{
		return score;
	}
}