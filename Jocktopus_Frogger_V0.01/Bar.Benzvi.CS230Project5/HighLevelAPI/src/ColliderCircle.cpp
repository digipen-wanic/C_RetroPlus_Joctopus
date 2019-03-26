//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "ColliderCircle.h"
#include "DebugDraw.h"
#include "Graphics.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"
#include "Intersection2D.h"
#include "ColliderRectangle.h"
#include "Parser.h"

ColliderCircle::ColliderCircle(float radius)
	: Collider(ColliderTypeCircle), radius(radius)
{
}


Component* ColliderCircle::Clone() const
{
	return new ColliderCircle(*this);
}

void ColliderCircle::Draw()
{
	DebugDraw::GetInstance().AddCircle(transform->GetTranslation(), radius, Graphics::GetInstance().GetCurrentCamera(), Colors::Green);
}

float ColliderCircle::GetRadius() const
{
	return radius;
}

void ColliderCircle::SetRadius(float radius_)
{
	radius = radius_;
}

// Loads object data from a file.
void ColliderCircle::Deserialize(Parser& parser)
{
	parser.ReadVariable("radius", radius);
}

// Saves object data to a file.
void ColliderCircle::Serialize(Parser& parser) const
{
	parser.WriteVariable("radius", radius);
}

bool ColliderCircle::IsCollidingWith(const Collider& other) const
{
	Transform* otherTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));

	Circle thisCircle(transform->GetTranslation(), radius);
	if (other.GetType() == ColliderTypePoint)
	{
		return PointCircleIntersection(otherTransform->GetTranslation(), thisCircle);
	}
	if (other.GetType() == ColliderTypeCircle)
	{
		Circle circle(otherTransform->GetTranslation(), static_cast<const ColliderCircle&>(other).GetRadius());

		return CircleCircleIntersection(thisCircle, circle);
	}
	else if (other.GetType() == ColliderTypeRectangle)
	{
		BoundingRectangle rect(otherTransform->GetTranslation(), static_cast<const ColliderRectangle&>(other).GetExtents());

		return RectangleCircleIntersection(rect, thisCircle);
	}
	else
	{
		return other.IsCollidingWith(*this);
	}
}
