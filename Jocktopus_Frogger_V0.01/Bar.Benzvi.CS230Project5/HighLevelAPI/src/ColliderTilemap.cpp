//------------------------------------------------------------------------------
//
// File Name:	ColliderTilemap.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "ColliderTilemap.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"
#include "ColliderRectangle.h"
#include "Physics.h"
#include "Shapes2D.h"
#include "Tilemap.h"


ColliderTilemap::ColliderTilemap()
	: Collider(ColliderTypeTilemap)
{
}

Component* ColliderTilemap::Clone() const
{
	return new ColliderTilemap(*this);
}

void ColliderTilemap::Draw()
{
}

void ColliderTilemap::SetTilemap(const Tilemap* map_)
{
	map = map_;
}

bool ColliderTilemap::IsCollidingWith(const Collider& other) const
{
	Transform* otherTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));
	Physics* otherPhys = static_cast<Physics*>(other.GetOwner()->GetComponent("Physics"));

	BoundingRectangle rectangle(otherTransform->GetTranslation(), static_cast<const ColliderRectangle&>(other).GetExtents());
	
	MapCollision mapCollision(IsSideColliding(rectangle, SideBottom), IsSideColliding(rectangle, SideTop), IsSideColliding(rectangle, SideLeft), IsSideColliding(rectangle, SideRight));

	if (other.GetMapCollisionHandler() == nullptr)
	{
		return false;
	}

	if (mapCollision.top || mapCollision.bottom || mapCollision.right || mapCollision.left)
	{
		ResolveCollisions(rectangle, otherTransform, otherPhys, mapCollision);

		other.GetMapCollisionHandler()(*other.GetOwner(), mapCollision);
		return true;
	}

	return false;
}

bool ColliderTilemap::IsSideColliding(const BoundingRectangle& rectangle, RectangleSide side) const
{
	Vector2D hotspot1;
	Vector2D hotspot2;

	if (side == SideBottom)
	{
		hotspot1 = Vector2D(rectangle.center.x + (rectangle.extents.x / 1.25f), rectangle.bottom);
		hotspot2 = Vector2D(rectangle.center.x - (rectangle.extents.x / 1.25f), rectangle.bottom);

	}
	else if (side == SideTop)
	{
		hotspot1 = Vector2D(rectangle.center.x + (rectangle.extents.x / 1.25f), rectangle.top);
		hotspot2 = Vector2D(rectangle.center.x - (rectangle.extents.x / 1.25f), rectangle.top);
	}
	else if (side == SideRight)
	{
		hotspot1 = Vector2D(rectangle.right, rectangle.center.y + (rectangle.extents.y / 1.25f));
		hotspot2 = Vector2D(rectangle.right, rectangle.center.y - (rectangle.extents.y / 1.25f));
	}
	else
	{
		hotspot1 = Vector2D(rectangle.left, rectangle.center.y + (rectangle.extents.y / 1.25f));
		hotspot2 = Vector2D(rectangle.left, rectangle.center.y - (rectangle.extents.y / 1.25f));
	}

	return IsCollidingAtPosition(hotspot1.x, hotspot1.y) || IsCollidingAtPosition(hotspot2.x, hotspot2.y);
}

bool ColliderTilemap::IsCollidingAtPosition(float x, float y) const
{
	Vector2D point(x, y);

	point = transform->GetInverseMatrix() * point;

	int column = static_cast<int>(point.x + 0.5);
	int row = static_cast<int>(-point.y + 0.5);

	if (map->GetCellValue(column, row) > 0)
	{
		return true;
	}

	return false;


}

void ColliderTilemap::ResolveCollisions(const BoundingRectangle& objectRectangle, Transform* objectTransform,
	Physics* objectPhysics, const MapCollision& collisions) const
{
	Vector2D objTranslation = objectTransform->GetTranslation();
	Vector2D objVel = objectPhysics->GetVelocity();

	float nudge = 0.0f;
	float nextCenter = 0.0f;

	if (collisions.bottom || collisions.top)
	{
		if (collisions.bottom)
		{
			nextCenter = GetNextTileCenter(SideBottom, objectRectangle.bottom);
			nudge = nextCenter - objectRectangle.bottom;
		}
		else
		{
			nextCenter = GetNextTileCenter(SideTop, objectRectangle.top);
			nudge = nextCenter - objectRectangle.top;
		}

		objTranslation.y += nudge;
		objVel.y = 0;
	}
	

	if (collisions.right || collisions.left)
	{
		if (collisions.right)
		{
			nextCenter = GetNextTileCenter(SideRight, objectRectangle.right);
			nudge = nextCenter - objectRectangle.right;
		}
		else
		{
			nextCenter = GetNextTileCenter(SideLeft, objectRectangle.left);
			nudge = nextCenter - objectRectangle.left;
		}

		objTranslation.x += nudge;
		objVel.x = 0;
	}

	objectTransform->SetTranslation(objTranslation);
	objectPhysics->SetVelocity(objVel);

}

float ColliderTilemap::GetNextTileCenter(RectangleSide side, float sidePosition) const
{
	Vector2D point(0.0f, 0.0f);
	float* result;

	if (side == SideBottom || side == SideTop)
	{
		point.y = sidePosition;
		result = &point.y;
	}
	else
	{
		point.x = sidePosition;
		result = &point.x;
	}

	point = transform->GetInverseMatrix() * point;

	point.y = -point.y;
	point += Vector2D(0.5f, 0.5f);


	if (side == SideTop || side == SideLeft)
	{
		*result = ceil(*result);
	}
	else
	{
		*result = floor(*result);
	}

	point -= Vector2D(0.5f, 0.5f);

	point.y = -point.y;

	point = transform->GetMatrix() * point;

	return *result;

}