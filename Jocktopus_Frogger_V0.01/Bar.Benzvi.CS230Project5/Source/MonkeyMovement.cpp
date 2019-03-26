//------------------------------------------------------------------------------
//
// File Name:	MonkeyMovement.cpp
// Author(s):	Bar Ben-zvi
// Project:		CS230 Lab 1: Objects and Sprites
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MonkeyMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Input.h"
#include "Collider.h"
#include "Space.h"
#include "Graphics.h"
#include "Interpolation.h"
#include "Parser.h"


namespace Behaviors
{
	MonkeyMovement::MonkeyMovement()
		: Component("MonkeyMovement"), monkeyWalkSpeed(400.0f), monkeyJumpSpeed(700.0f), gravity(0.0f, -1200.0f)
	{
	}

	Component* MonkeyMovement::Clone() const
	{
		return new MonkeyMovement(*this);
	}

	void MonkeyMapCollisionHandler(GameObject& object, const MapCollision& collision)
	{
		if (collision.bottom)
		{
			static_cast<MonkeyMovement*>(object.GetComponent("MonkeyMovement"))->onGround = true;
		}
	}

	void MonkeyCollisionHandler(GameObject& object, GameObject& other)
	{

		if (other.GetName() == "Collectible")
		{
			other.Destroy();
		}
		else if (other.GetName() == "Hazard")
		{
			object.GetSpace()->RestartLevel();
		}
		else if (other.GetName() == "Enemy")
		{
			object.GetSpace()->RestartLevel();
		}

	}

	void MonkeyMovement::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));

		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(MonkeyMapCollisionHandler);
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(MonkeyCollisionHandler);

		//transform->SetTranslation(Vector2D(transform->GetTranslation().x, groundHeight));
	}


	void MonkeyMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		MoveHorizontal();
		MoveVertical();

		//Camera& camera = Graphics::GetInstance().GetCurrentCamera();

		//camera.SetTranslation(Interpolate(camera.GetTranslation(), transform->GetTranslation(), 3.0f * dt));
	}


	void MonkeyMovement::MoveHorizontal() const
	{
		physics->SetVelocity(Vector2D(0, physics->GetVelocity().y));

		if(Input::GetInstance().CheckHeld(VK_LEFT))
		{
			physics->SetVelocity(Vector2D(-monkeyWalkSpeed, physics->GetVelocity().y));
		}
		else if(Input::GetInstance().CheckHeld(VK_RIGHT))
		{
			physics->SetVelocity(Vector2D(monkeyWalkSpeed, physics->GetVelocity().y));
		}
	}

	

	// Loads object data from a file.
	void MonkeyMovement::Deserialize(Parser& parser)
	{
		parser.ReadVariable("monkeyWalkSpeed", monkeyWalkSpeed);
		parser.ReadVariable("monkeyJumpSpeed", monkeyJumpSpeed);
		parser.ReadVariable("gravity", gravity);
	}

	// Saves object data to a file.
	void MonkeyMovement::Serialize(Parser& parser) const
	{
		parser.WriteVariable("monkeyWalkSpeed", monkeyWalkSpeed);
		parser.WriteVariable("monkeyJumpSpeed", monkeyJumpSpeed);
		parser.WriteVariable("gravity", gravity);
	}

	void MonkeyMovement::MoveVertical()
	{
		if(onGround)
		{
			if (Input::GetInstance().CheckTriggered(VK_UP))
			{
				physics->SetVelocity(Vector2D(physics->GetVelocity().x, monkeyJumpSpeed));
				onGround = false;
			}
			if (physics->GetVelocity().y < -100.0f)
			{
				onGround = false;
			}

		}

		physics->AddForce(gravity);

		if (physics->GetVelocity().y < -500.0f)
		{
			physics->SetVelocity(Vector2D(physics->GetVelocity().x, -500.0f));
		}

	}
}