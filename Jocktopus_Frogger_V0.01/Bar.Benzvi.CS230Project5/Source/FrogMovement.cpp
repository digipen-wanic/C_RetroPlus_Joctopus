//------------------------------------------------------------------------------
//
// File Name:	FrogMovement.cpp
// Author(s):	Freddy Martin, Bar Ben-zvi
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
	int FrogMovement::highScore = 0;
	int FrogMovement::furthestForward = 0;
	int FrogMovement::lives = 2;

	FrogMovement::FrogMovement(float speed, int walkFrames, float deathTime)
		:Component("FrogMovement"), speed(speed), canWalk(0), walkFrames(walkFrames), dying(false),
		currentForward(0), currX(1), onFloat(false), deathTime(deathTime), timer(0), loseTimer(40.0f), waterDeathActive(false),
		purpleFrogActive(false), deathAnimation(nullptr), drownAnimation(nullptr), destroyNextFrame(false), ribbitSoundName("WinRibbit.wav"),
		jumpSoundName("Jump.wav"), deathSoundName("DieExplosion.wav")
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

		if (other.GetName() == "Car" || other.GetName() == "Snake")
		{
			movement->InitDeathSequence();
		}
		else if (other.GetName() == "PFrog")
		{
			movement->purpleFrogActive = true;
			object.GetComponent<Sprite>()->SetFrame(0);
			object.GetComponent<Sprite>()->SetSpriteSource(movement->purpleSpriteSource);
			other.Destroy();
		}
		else if (other.GetName() == "WinSlot" && !other.GetComponent<WinSlot>()->GetContainsFrog())
		{

			GameObject* winFrog = GameObjectFactory::GetInstance().CreateObject("WinFrog", movement->winMesh, movement->winSpriteSource);
			winFrog->GetComponent<Transform>()->SetTranslation(other.GetComponent<Transform>()->GetTranslation());

			other.GetComponent<WinSlot>()->SetContainsFrog(true);

			object.GetSpace()->GetObjectManager().AddObject(*winFrog);

			int timerScore = static_cast<int>((movement->loseTimer * 20.0f));

			movement->score += timerScore + 50;

			Engine::GetInstance().GetModule<SoundManager>()->PlaySound(movement->ribbitSoundName);

			if (movement->purpleFrogActive)
			{
				movement->score += 100;
			}

			movement->furthestForward = 0;

			movement->destroyNextFrame = true;
		}
		else if ((other.GetName() == "Log" || other.GetName() == "Turtle") && !object.GetComponent<FrogMovement>()->dying)
		{
			if (other.GetComponent<TurtleMovement>() == nullptr || other.GetComponent<TurtleMovement>()->IsStandable())
			{
				object.GetComponent<FrogMovement>()->onFloat = true;
				object.GetComponent<Physics>()->SetVelocity(Vector2D(other.GetComponent<ItemMovement>()->GetSpeed() * other.GetComponent<ItemMovement>()->GetDirection(), 0));
			}
		}

		if (movement->score > movement->highScore)
		{
			movement->highScore = movement->score;
		}
	}

	void FrogMovement::Initialize()
	{
		soundManager = Engine::GetInstance().GetModule<SoundManager>();

		// Init collision handler
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(FrogCollisionHandler);
	}

	void FrogMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		Input& input = Input::GetInstance();

		if (destroyNextFrame)
		{
			GetOwner()->Destroy();
		}

		// Runs movement if the player isn't dying
		if (!dying && !destroyNextFrame)
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
					canWalk = 8;
					currentForward++;

					soundManager->PlaySound(jumpSoundName);

					// Checks if the player has moved further forward than before and sets the furthest forward if they have
					if (currentForward > furthestForward)
					{
						score += (currentForward - furthestForward) * 10;
						furthestForward = currentForward;

						if (score > highScore)
						{
							highScore = score;
						}
					}
				}
				// If the player isn't at the bottom and s is pressed, move down
				else if (currentForward > 0 && input.CheckTriggered('S'))
				{
					

					GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(0, speed));
					GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI);
					GetOwner()->GetComponent<Sprite>()->SetFrame(2);
					canWalk = 8;

					// If currentForward - 1 is greater than 0, we can move
					if (currentForward - 1 >= 0)
					{
						currentForward -= 1;
						soundManager->PlaySound(jumpSoundName);
					}
					
				}
				else if (input.CheckTriggered('D'))
				{
					float currXTranslation = GetOwner()->GetComponent<Transform>()->GetTranslation().x;

					currX = static_cast<int>(currXTranslation / 48.0f);

					if (currX <= 5)
					{
						GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(speed, 0));
						GetOwner()->GetComponent<Transform>()->SetRotation(-(float)M_PI / 2.0f);
						GetOwner()->GetComponent<Sprite>()->SetFrame(2);
						canWalk = 8;
						soundManager->PlaySound(jumpSoundName);

						currX += 1;
					}

				}
				else if (input.CheckTriggered('A'))
				{
					float currXTranslation = GetOwner()->GetComponent<Transform>()->GetTranslation().x;

					currX = static_cast<int>(currXTranslation / 48.0f);

					if (currX >= -5)
					{
						GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() - Vector2D(speed, 0));
						GetOwner()->GetComponent<Transform>()->SetRotation((float)M_PI / 2.0f);
						GetOwner()->GetComponent<Sprite>()->SetFrame(2);

						canWalk = 8;
						soundManager->PlaySound(jumpSoundName);

						currX -= 1;
					}
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
			
			--lives;
			GetOwner()->GetComponent<Transform>()->SetRotation(0);
			if (!waterDeathActive)
			{
				soundManager->PlaySound(deathSoundName);
				GetOwner()->GetComponent<Sprite>()->SetSpriteSource(deathAnimation);
			}
			else
			{
				soundManager->PlaySound("DieBubbles.wav");
				GetOwner()->GetComponent<Sprite>()->SetSpriteSource(drownAnimation);
			}
			
			GetOwner()->GetComponent<Animation>()->Play(0, 4, 0.5f, false);
		}
	}

	void FrogMovement::SetDeathAnimations(SpriteSource* deathAnimation_, SpriteSource* drownAnimation_)
	{
		deathAnimation = deathAnimation_;
		drownAnimation = drownAnimation_;
	}

	
	int FrogMovement::GetScore()
	{
		return score;
	}

	void FrogMovement::ResetScore()
	{
		score = 0;
		furthestForward = 0;
		lives = 2;
	}

	int FrogMovement::GetHighScore()
	{
		return highScore;
	}

	float FrogMovement::GetTimer() const
	{
		return loseTimer;
	}

	int FrogMovement::GetLives()
	{
		return lives;
	}

	void FrogMovement::SetLives(int newLives)
	{
		lives = newLives;
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

	void FrogMovement::SetSounds(std::string soundName, std::string soundName2, std::string soundName3)
	{
		ribbitSoundName = soundName;
		jumpSoundName = soundName2;
		deathSoundName = soundName3;
	}

}