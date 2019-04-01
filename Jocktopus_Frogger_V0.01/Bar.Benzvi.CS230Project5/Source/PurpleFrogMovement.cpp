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
			
			object.GetComponent<Physics>()->SetVelocity(Vector2D(other.GetComponent<ItemMovement>()->GetSpeed() * other.GetComponent<ItemMovement>()->GetDirection(), 0));

			if (((object.GetComponent<Transform>()->GetTranslation().x - (object.GetComponent<Transform>()->GetScale().x / 4)) != other.GetComponent<Transform>()->GetTranslation().x) && ((object.GetComponent<Transform>()->GetTranslation().x + (object.GetComponent<Transform>()->GetScale().x / 4) != other.GetComponent<Transform>()->GetTranslation().x)))
			{
				//std::cout << object.GetComponent<Transform>()->GetTranslation().x - (object.GetComponent<Transform>()->GetScale().x / 3) << " !=" << other.GetComponent<Transform>()->GetTranslation().x << std::endl;
				//object.GetComponent<Transform>()->SetTranslation(other.GetComponent<Transform>()->GetTranslation() - Vector2D(object.GetComponent<Transform>()->GetScale().x/4, 0));
				//object.GetComponent<PurpleFrogMovement>()->SetDirection(1);
			}
		}
	}
	void PurpleFrogMovement::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(PFrogCollisionHandler);
		timer = 0;
		std::cout << "Pfrog" << std::endl;
	}
	void PurpleFrogMovement::Update(float dt)
	{
		timer += dt;
		if (timer >= delay)
		{
			GetOwner()->GetComponent<Transform>()->SetTranslation(GetOwner()->GetComponent<Transform>()->GetTranslation() + Vector2D(speed * direction, 0));
			direction *= -1;
			timer = 0;
		}
	}

	void PurpleFrogMovement::SetDirection(int dir)
	{
		direction = dir;
	}
	
}
