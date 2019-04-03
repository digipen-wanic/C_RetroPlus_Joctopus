/*
By: Kyle Jamison
SnakeMovement
3/28/19
Purple Frog Movment
*/

#include "stdafx.h"
#include "SnakeMovement.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"



namespace Behaviors
{
	SnakeMovement::SnakeMovement(float speed, int direction, bool flaot)
		:Component("SnakeMovement"), onLog(true), speed(speed), direction(direction), floats(flaot)
	{
	}
	Component * SnakeMovement::Clone() const
	{
		return new SnakeMovement(*this);
	}

	void SnakeCollisionHandler(GameObject & object, GameObject & other)
	{
		if (other.GetName() == "Log")
		{
			object.GetComponent<SnakeMovement>()->SetOnLog(true);
		}
		if (other.GetName() == "Wall")
		{
			object.GetComponent<SnakeMovement>()->SetDirection(object.GetComponent<SnakeMovement>()->GetDirection() * -1);
		}
	}

	void SnakeMovement::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(SnakeCollisionHandler);
	}
	void SnakeMovement::Update(float dt)
	{
		if (onLog || !floats)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x + (speed * direction * dt), transform->GetTranslation().y));
		}
		else
		{
			direction *= -1;
		}
		onLog = false;
	}
	void SnakeMovement::SetDirection(int dir)
	{
		direction = dir;
	}
	int SnakeMovement::GetDirection()
	{
		return direction;
	}
	void SnakeMovement::SetOnLog(bool log)
	{
		onLog = log;
	}
	
}