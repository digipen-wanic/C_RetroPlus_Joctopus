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
	ItemMovement::ItemMovement(float speed, bool left)
		: Component("ItemMovement"), moveLeft(left), speed(speed)
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
		if (moveLeft)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x + (speed * dt), transform->GetTranslation().y));
		}
		else
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x - (speed * dt), transform->GetTranslation().y));
		}
	}
	void ItemMovement::SetSpeed(float Speed)
	{
		speed = Speed;
	}
	void ItemMovement::SetLeft(bool Left)
	{
		moveLeft = Left;
	}
}