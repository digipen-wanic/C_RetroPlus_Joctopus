/*
By: Kyle Jamison
PurpleFrogMovement
3/28/19
Purple Frog Movment
*/
#include "stdafx.h"
#include "PurpleFrogMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "ItemMovement.h"
#include "Collider.h"

namespace Behaviors
{
	PurpleFrogMovement::PurpleFrogMovement(float delay, float speed, int direction)
		:Component("PurpleFrogMovement"), delay(delay), timer(0), direction(direction), speed(speed)
	{}
	Component * PurpleFrogMovement::Clone() const
	{
		return new PurpleFrogMovement(*this);
	}
	void PFrogCollisionHandler(GameObject & object, GameObject & other)
	{
		if (other.GetName() == "Log")
		{
			object.GetComponent<PurpleFrogMovement>()->SetOnLog(true);
			object.GetComponent<Physics>()->SetVelocity(Vector2D(other.GetComponent<ItemMovement>()->GetSpeed() * other.GetComponent<ItemMovement>()->GetDirection(), 0));

			if (object.GetComponent<Transform>()->GetTranslation().x - other.GetComponent<Transform>()->GetTranslation().x > 0)
			{
				object.GetComponent<PurpleFrogMovement>()->SetDirection(-1);
			}
			else
			{
				object.GetComponent<PurpleFrogMovement>()->SetDirection(1);
			}
		}
	}
	void PurpleFrogMovement::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(PFrogCollisionHandler);
		timer = 0;
		std::cout << "Pfrog" << std::endl;
		fellOff = false;
		fixed = true;
	}
	void PurpleFrogMovement::Update(float dt)
	{
		timer += dt;
		if (onLog == false)
		{
			GetOwner()->GetComponent<Physics>()->SetVelocity(Vector2D(0, 0));
		}
		if (timer >= delay)
		{


			if (onLog == true)
			{
				transform->SetTranslation(transform->GetTranslation() + Vector2D(speed * direction, 0));

				direction *= -1;
				timer = 0;
				
				onLog = false;
			}
			
		}
		
	}

	void PurpleFrogMovement::SetDirection(int dir)
	{
		direction = dir;
	}

	void PurpleFrogMovement::SetOnLog(bool log)
	{
		onLog = log;
	}
	
}
