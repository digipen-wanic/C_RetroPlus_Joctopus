//------------------------------------------------------------------------------
//
// File Name:	PlayerShip.cpp
// Author(s):	Bar Ben-zvi
// Project:		CS230 Lab 2: Archetypes and Serialization
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "PlayerShip.h"
#include "Transform.h"
#include "GameObject.h"
#include "Physics.h"
#include "Input.h"
#include "Space.h"
#include "TimedDeath.h"
#include "Parser.h"
#include "Engine.h"
#include "PlayerProjectile.h"
#include "Math.h"
#include "Sprite.h"
#include "Collider.h"
#include "Graphics.h"

namespace Behaviors
{

	PlayerShip::PlayerShip(float forwardThrust, float maximumSpeed, float rotationSpeed, float bulletSpeed, float deathDuration)
		: Component("PlayerShip"), forwardThrust(forwardThrust), maximumSpeed(maximumSpeed), rotationSpeed(rotationSpeed), bulletSpeed(bulletSpeed),
		  deathDuration(deathDuration), isDying(false), score(0)
	{

	}

	Component* PlayerShip::Clone() const
	{
		return new PlayerShip(*this);
	}

	/*PlayerShip::~PlayerShip()
	{
	}*/

	static void CollisionHandlerShip(GameObject& ship, GameObject& otherObject)
	{

		if (otherObject.GetName() == "Asteroid" && !ship.GetComponent<PlayerShip>()->isDying)
		{
			ship.GetComponent<PlayerShip>()->timer = ship.GetComponent<PlayerShip>()->deathDuration;
			ship.GetComponent<PlayerShip>()->isDying = true;
			ship.GetComponent<PlayerShip>()->timer2 = 0.0f;
		}
	}

	void PlayerShip::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		physics = GetOwner()->GetComponent<Physics>();
		bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");


		Collider* collider = GetOwner()->GetComponent<Collider>();
		collider->SetCollisionHandler(&CollisionHandlerShip);
	}

	void PlayerShip::Serialize(Parser& parser) const
	{
		parser.WriteVariable("forwardThrust", forwardThrust);
		parser.WriteVariable("rotationSpeed", rotationSpeed);
		parser.WriteVariable("bulletSpeed", bulletSpeed);
		parser.WriteVariable("deathDuration", deathDuration);
	}

	void PlayerShip::Deserialize(Parser& parser)
	{
		parser.ReadVariable("forwardThrust", forwardThrust);
		parser.ReadVariable("rotationSpeed", rotationSpeed);
		parser.ReadVariable("bulletSpeed", bulletSpeed);
		parser.ReadVariable("deathDuration", deathDuration);

	}

	void PlayerShip::Update(float dt)
	{
		if (!isDying)
		{
			Move();
			Rotate();
			Shoot();
		}
		else
		{
			DeathSequence(dt);
		}
	}

	

	void PlayerShip::Move() const
	{
		if (Input::GetInstance().CheckHeld('W') || Input::GetInstance().CheckHeld(VK_UP))
		{
			physics->AddForce(Vector2D::FromAngleRadians(transform->GetRotation()) * forwardThrust);

			if (physics->GetVelocity().Magnitude() > maximumSpeed)
			{
				physics->SetVelocity(physics->GetVelocity().Normalized() * maximumSpeed);
			}
		}
	}

	void PlayerShip::Rotate() const
	{
		if (Input::GetInstance().CheckHeld('A') || Input::GetInstance().CheckHeld(VK_LEFT))
		{
			physics->SetAngularVelocity(rotationSpeed);
		}
		else if (Input::GetInstance().CheckHeld('D') || Input::GetInstance().CheckHeld(VK_RIGHT))
		{
			physics->SetAngularVelocity(-rotationSpeed);
		}
		else
		{
			physics->SetAngularVelocity(0);
		}
	}

	void PlayerShip::Shoot()
	{
		if ((Input::GetInstance().CheckTriggered(' ') || Input::GetInstance().CheckTriggered(VK_LBUTTON)))
		{
			//Vector2D mousePos = Input::GetInstance().GetCursorPosition();

			GameObject* newBullet = new GameObject(*bulletArchetype);
			Vector2D dir = Vector2D::FromAngleRadians(transform->GetRotation());
			newBullet->GetComponent<Transform>()->SetTranslation(transform->GetTranslation() + (dir * transform->GetScale().x / 2));
			newBullet->GetComponent<Transform>()->SetRotation(transform->GetRotation());

			newBullet->GetComponent<Physics>()->SetVelocity((dir * bulletSpeed) + physics->GetVelocity());
			newBullet->GetComponent<PlayerProjectile>()->SetSpawner(this);

			GetOwner()->GetSpace()->GetObjectManager().AddObject(*newBullet);
		}
	}

	void PlayerShip::IncreaseScore(unsigned amount)
	{
		score += amount;
	}

	unsigned PlayerShip::GetScore() const
	{
		return score;
	}

	//Basically a comparison operator between 2 colors
	//Compares the rgba values of c1 and c2
	//Returns true or false based on wether the color's rgba values are the same
	bool CompareColors(Color c1, Color c2)
	{
		if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a)
		{
			return true;
		}

		return false;
	}

	void PlayerShip::DeathSequence(float dt)
	{
		timer -= dt;
		timer2 -= dt;

		if (timer <= 0)
		{
			Graphics::GetInstance().SetBackgroundColor(Colors::Black);
			GetOwner()->GetSpace()->RestartLevel();
		}
		else
		{
			if (timer2 <= 0)
			{
				if (CompareColors(Graphics::GetInstance().GetBackgroundColor(), Colors::Red))
				{
					Graphics::GetInstance().SetBackgroundColor(Colors::Orange);
				}
				else
				{
					Graphics::GetInstance().SetBackgroundColor(Colors::Red);
				}
				timer2 = 0.5f;
			}

			physics->SetAngularVelocity((rotationSpeed * rotationSpeed));
		}
		
	}

	
}