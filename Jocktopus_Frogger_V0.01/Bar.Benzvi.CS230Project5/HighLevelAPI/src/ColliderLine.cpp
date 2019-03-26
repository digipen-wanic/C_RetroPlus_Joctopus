//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ColliderLine.h"
#include "Parser.h"
#include "Transform.h"
#include "DebugDraw.h"
#include "Camera.h"
#include "Graphics.h"
#include "Physics.h"
#include "GameObject.h"

ColliderLine::ColliderLine(bool reflection)
	: Collider(ColliderTypeLines), reflection(reflection)
{
}

Component* ColliderLine::Clone() const
{
	return new ColliderLine(*this);
}

void ColliderLine::Draw()
{
	for (unsigned i = 0; i < lineSegments.size(); ++i)
	{
		LineSegment currSegment = GetLineWithTransform(i);
		Vector2D normStart = currSegment.normal + (currSegment.start.Midpoint(currSegment.end));
		Vector2D normEnd = normStart + (currSegment.normal * 20);

		DebugDraw::GetInstance().AddLineToStrip(currSegment.start, currSegment.end, Colors::Green);
		DebugDraw::GetInstance().AddLineToStrip(normStart, normEnd, Colors::Red);

	}

	DebugDraw::GetInstance().EndLineStrip(Graphics::GetInstance().GetDefaultCamera());
}

void ColliderLine::AddLineSegment(const Vector2D& p0, const Vector2D& p1)
{
	lineSegments.push_back(LineSegment(p0, p1));
}

bool ColliderLine::IsCollidingWith(const Collider& other) const
{
	if (other.GetType() == ColliderTypePoint || other.GetType() == ColliderTypeCircle)
	{


		LineSegment otherLine(other.physics->GetOldTranslation(), other.transform->GetTranslation());

		for (int i = 0; i < lineSegments.size(); ++i)
		{
			LineSegment curr = GetLineWithTransform(i);
			Vector2D intersection(0, 0);
			float t = 0;

			if (MovingPointLineIntersection(curr, otherLine, intersection, t))
			{
				if (reflection)
				{
					MovingPointLineReflection(*other.transform, *other.physics, curr, otherLine, intersection);
				}

				return true;
			}
		}
	}

	return false;

}

void ColliderLine::Serialize(Parser& parser) const
{
	size_t count = lineSegments.size();
	parser.WriteVariable("lineCount", count);
	parser.WriteValue("lines :");
	parser.BeginScope();

	for (int i = 0; i < count; ++i)
	{
		parser.WriteValue(lineSegments[i]);
	}

	parser.EndScope();
}

void ColliderLine::Deserialize(Parser& parser)
{
	int count;
	parser.ReadVariable("lineCount", count);
	parser.ReadSkip("lines");
	parser.ReadSkip(':');
	parser.ReadSkip('{');

	for (int i = 0; i < count; ++i)
	{
		LineSegment segment;
		parser.ReadValue(segment);
		lineSegments.push_back(segment);
	}

	parser.ReadSkip('}');
}

LineSegment ColliderLine::GetLineWithTransform(unsigned index) const
{
	if (index >= lineSegments.size())
	{
		exit(-1);
	}

	LineSegment ls = lineSegments[index];

	ls.end = transform->GetMatrix() * ls.end;
	ls.start = transform->GetMatrix() * ls.start;

	return ls;
}