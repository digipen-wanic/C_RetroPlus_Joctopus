/*
By: Kyle Jamison
ItemMovement
3/27/19
Move the thing
*/
#include "stdafx.h"
#include "ItemMovement.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector2D.h"

namespace Behaviors
{
	ItemMovement::ItemMovement(float speed, int dir)
		: Component("ItemMovement"), direction(dir), speed(speed)
	{}
	Component * ItemMovement::Clone() const
	{
		return new ItemMovement(*this);
	}
	void ItemMovement::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
	}
	void ItemMovement::Update(float dt)
	{
		transform->SetTranslation(Vector2D(transform->GetTranslation().x + (speed * direction * dt), transform->GetTranslation().y));
	}
	void ItemMovement::SetSpeed(float Speed)
	{
		speed = Speed;
	}
	float ItemMovement::GetSpeed()
	{
		return speed;
	}
	void ItemMovement::SetDirection(int dir)
	{
		direction = dir;
	}
	int ItemMovement::GetDirection() const
	{
		return direction;
	}
}