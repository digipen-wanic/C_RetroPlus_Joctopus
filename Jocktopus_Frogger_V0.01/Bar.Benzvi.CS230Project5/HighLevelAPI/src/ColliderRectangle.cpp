//------------------------------------------------------------------------------
//
// File Name:	ColliderRectangle.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "ColliderRectangle.h"
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "DebugDraw.h"
#include "Transform.h"
#include "GameObject.h"
#include "Graphics.h"
#include "Intersection2D.h"
#include "Parser.h"



ColliderRectangle::ColliderRectangle(const Vector2D& extents)
	: Collider(ColliderTypeRectangle), extents(extents)
{
}

Component* ColliderRectangle::Clone() const
{
	return new ColliderRectangle(*this);
}

void ColliderRectangle::Draw()
{
	DebugDraw::GetInstance().AddRectangle(transform->GetTranslation(), extents, Graphics::GetInstance().GetCurrentCamera(), Colors::Green);
}

const Vector2D& ColliderRectangle::GetExtents() const
{
	return extents;
}

void ColliderRectangle::SetExtents(const Vector2D& extents_)
{
	extents = extents_;
}

bool ColliderRectangle::IsCollidingWith(const Collider& other) const
{
	Transform* otherTransform = static_cast<Transform*>(other.GetOwner()->GetComponent("Transform"));

	BoundingRectangle thisRect(transform->GetTranslation(), extents);

	if (other.GetType() == ColliderTypePoint)
	{
		return PointRectangleIntersection(otherTransform->GetTranslation(), thisRect);
	}
	if (other.GetType() == ColliderTypeCircle)
	{
		Circle circle(otherTransform->GetTranslation(), static_cast<const ColliderCircle&>(other).GetRadius());

		return RectangleCircleIntersection(thisRect, circle);
	}
	else if (other.GetType() == ColliderTypeRectangle)
	{
		BoundingRectangle rect(otherTransform->GetTranslation(), static_cast<const ColliderRectangle&>(other).GetExtents());

		return RectangleRectangleIntersection(thisRect, rect);
	}
	else
	{
		other.IsCollidingWith(*this);
	}

	return false;
}

// Loads object data from a file.
void ColliderRectangle::Deserialize(Parser& parser)
{
	parser.ReadVariable("extents", extents);
}

// Saves object data to a file.
void ColliderRectangle::Serialize(Parser& parser) const
{
	parser.WriteVariable("extents", extents);
}