//------------------------------------------------------------------------------
//
// File Name:	ColliderPoint.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "ColliderPoint.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"
#include "DebugDraw.h"
#include "Graphics.h"
#include "Intersection2D.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"

ColliderPoint::ColliderPoint()
	: Collider(ColliderTypePoint)
{

}

Component* ColliderPoint::Clone() const
{
	return new ColliderPoint(*this);
}

void ColliderPoint::Draw()
{
	DebugDraw::GetInstance().AddCircle(transform->GetTranslation(), 10.0f, Graphics::GetInstance().GetCurrentCamera(), Colors::Green);
	
}

bool ColliderPoint::IsCollidingWith(const Collider& other) const
{

	Transform* otherTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));

	if (other.GetType() == ColliderTypePoint && AlmostEqual(transform->GetTranslation(), otherTransform->GetTranslation()))
	{
		return true;
	}
	else if (other.GetType() == ColliderTypeCircle)
	{
		Circle circle(otherTransform->GetTranslation(), static_cast<const ColliderCircle&>(other).GetRadius());

		return PointCircleIntersection(transform->GetTranslation(), circle);
	}
	else if (other.GetType() == ColliderTypeRectangle)
	{
		BoundingRectangle rect(otherTransform->GetTranslation(), static_cast<const ColliderRectangle&>(other).GetExtents());

		return PointRectangleIntersection(transform->GetTranslation(), rect);
	}

	return false;
}