//------------------------------------------------------------------------------
//
// File Name:	FrogMovement.cpp
// Author(s):	Freddy Martin, Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
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
#include "GameObjectFactory.h"
#include "SpriteSource.h"
#include "Texture.h"
#include "MeshHelper.h"
#include "GameObjectManager.h"
#include "TurtleMovement.h"
#include "WinSlot.h"

namespace Behaviors
{
	int FrogMovement::score = 0;
	int FrogMovement::furthestForward = 0;
	int FrogMovement::lives = 2;

	FrogMovement::FrogMovement(float speed, int walkFrames, float deathTime)
		:Component("FrogMovement"), speed(speed), canWalk(0), walkFrames(walkFrames), dying(false), 
		currentForward(0), onFloat(false), deathTime(deathTime), timer(0), loseTimer(40.0f), waterDeathActive(false),
		purpleFrogActive(false), deathAnimation(nullptr), drownAnimation(nullptr)
	{
	}

	Component * FrogMovement::Clone() const
	{
		return new FrogMovement(*this);
	}

	void FrogCollisionHandler(GameObject& object, GameObject& other)
	{
		FrogMovement* movement = object.GetComponent<FrogMovement>();

		if (other.GetName() == "Fly")
		{
			movement->score += 100;
			other.Destroy();
		}

		if (other.GetName() == "Car")
		{
			movement->InitDeathSequence();
		}
		else if (other.GetName() == "PFrog")
		{
			movement->purpleFrogActive = true;
			object.GetComponent<Sprite>()->SetSpriteSource(movement->purpleSpriteSource);
			other.Destroy();
		}
		else if (other.GetName() == "WinSlot" && !other.GetComponent<WinSlot>()->GetContainsFrog())
		{

			GameObject* winFrog = GameObjectFactory::GetInstance().CreateObject("WinFrog", movement->winMesh, movement->winSpriteSource);
			winFrog->GetComponent<Transform>()->SetTranslation(other.GetComponent<Transform>()->GetTranslation());

			object.GetSpace()->GetObjectManager().AddObject(*winFrog);

			int timerScore = static_cast<int>((movement->loseTimer * 20.0f));

			movement->score += timerScore + 50;

			if (movement->purpleFrogActive)
			{
				movement->score += 100;
			}

			object.Destroy();
		}
		else if ((other.GetName() == "Log" || other.GetName() == "Turtle") && !object.GetComponent<FrogMovement>()->dying)
		{
			
			if (object.GetComponent<FrogMovement>()->canWalk <= 0 || 
				(other.GetComponent<TurtleMovement>() != nullptr && other.GetComponent<TurtleMovement>()->IsStandable()))
			{
				object.GetComponent<FrogMovement>()->onFloat = true;
				object.GetComponent<Physics>()->SetVelocity(Vector2D(other.GetComponent<ItemMovement>()->GetSpeed() * other.GetComponent<ItemMovement>()->GetDirection(), 0));
			}
		}
	}

	void FrogMovement::Initialize()
	{
		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->AddEffect("Jump.wav");
		soundManager->AddEffect("DieExplosion.wav");

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

			loseTimer -= dt;

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
					GetOwner()->GetComponent<Sprite>()->SetFrame(2);
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
					GetOwner()->GetComponent<Sprite>()->SetFrame(2);
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
					GetOwner()->GetComponent<Sprite>()->SetFrame(2);
					canWalk = 2;
					soundManager->PlaySound("Jump.wav");
				}
				if (input.CheckTriggered('A'))
				{
					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(speed, 0));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI / 2.0f);
					GetOwner()->GetComponent<Sprite>()->SetFrame(2);
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
		if (currentForward > 6 && !onFloat && waterDeathActive)
		{
			InitDeathSequence();
		}
		else if (currentForward > 6 && !onFloat)
		{
			waterDeathActive = true;
		}
		else
		{
			waterDeathActive = false;
		}

		if (!onFloat || canWalk > 0)
		{
			GetOwner()->GetComponent<Physics>()->SetVelocity(Vector2D(0, 0));
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
			soundManager->PlaySound("DieExplosion.wav");
			--lives;
			GetOwner()->GetComponent<Transform>()->SetRotation(0);
			if (!waterDeathActive)
			{
				GetOwner()->GetComponent<Sprite>()->SetSpriteSource(deathAnimation);
			}
			else
			{
				GetOwner()->GetComponent<Sprite>()->SetSpriteSource(drownAnimation);
			}
			
			GetOwner()->GetComponent<Animation>()->Play(0, 4, 0.5f, false);
		}
	}

	void FrogMovement::SetDeathAnimations(SpriteSource* deathAnimation_, SpriteSource* drownAnimation_)
	{
		if (deathAnimation != nullptr)
		{
			delete deathAnimation;
		}
		if (drownAnimation != nullptr)
		{
			delete drownAnimation;
		}
		deathAnimation = deathAnimation_;
		drownAnimation = drownAnimation_;
	}

	

	int FrogMovement::GetScore() const
	{
		return score;
	}

	float FrogMovement::GetTimer() const
	{
		return loseTimer;
	}

	int FrogMovement::GetLives()
	{
		return lives;
	}

	void FrogMovement::SetWinSprite(Mesh* mesh, SpriteSource* spriteSource)
	{
		winMesh = mesh;
		winSpriteSource = spriteSource;
	}

	void FrogMovement::SetPurpleSprite(SpriteSource* spriteSource)
	{
		purpleSpriteSource = spriteSource;
	}
}