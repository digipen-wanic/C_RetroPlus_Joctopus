//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"


MapCollision::MapCollision(bool bottom, bool top, bool left, bool right)
	: bottom(bottom), top(top), left(left), right(right)
{
}

Collider::Collider(ColliderType type)
	: Component("Collider"), type(type), handler(nullptr), mapHandler(nullptr)
{
}

void Collider::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));

}

void Collider::CheckCollision(const Collider& other)
{
	if (IsCollidingWith(other))
	{
		if (handler != nullptr)
		{
			handler(*GetOwner(), *other.GetOwner());
		}
		if (other.handler != nullptr)
		{
			other.handler(*other.GetOwner(), *GetOwner());
		}
	}
}

ColliderType Collider::GetType() const
{
	return type;
}

void Collider::SetCollisionHandler(CollisionEventHandler handler_)
{
	handler = handler_;
}

void Collider::SetMapCollisionHandler(MapCollisionEventHandler mapHandler_)
{
	mapHandler = mapHandler_;
}

MapCollisionEventHandler Collider::GetMapCollisionHandler() const
{
	return mapHandler;
}

