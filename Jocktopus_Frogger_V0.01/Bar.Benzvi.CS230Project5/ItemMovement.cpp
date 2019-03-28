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
	void ItemMovement::Initialize()
	{
		transform = GetOwner()->GetComponent<Transform>();
	}
	void ItemMovement::Update()
	{
		if (moveLeft)
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x - speed, transform->GetTranslation().y));
		}
		else
		{
			transform->SetTranslation(Vector2D(transform->GetTranslation().x + speed, transform->GetTranslation().y));
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