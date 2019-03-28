//------------------------------------------------------------------------------
//
// File Name:	Intersection2D.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Transform.h"
#include "Intersection2D.h"
#include "Physics.h"

bool PointCircleIntersection(const Vector2D& point, const Circle& circle)
{
	if (point.DistanceSquared(circle.center) <= circle.radius * circle.radius)
	{
		return true;
	}

	return false;
}

bool PointRectangleIntersection(const Vector2D& point, const BoundingRectangle& rect)
{
	if (point.x < rect.left || point.x > rect.right || point.y < rect.bottom || point.y > rect.top)
	{
		return false;
	}

	return true;
}

bool CircleCircleIntersection(const Circle& circle1, const Circle& circle2)
{
	if (circle1.center.DistanceSquared(circle2.center) <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius))
	{
		return true;
	}

	return false;
}

bool RectangleRectangleIntersection(const BoundingRectangle& rect1, const BoundingRectangle& rect2)
{
	if (rect1.top < rect2.bottom || rect1.bottom > rect2.top || rect1.left > rect2.right || rect1.right < rect2.left)
	{
		return false;
	}

	return true;
}

bool RectangleCircleIntersection(const BoundingRectangle& rect, const Circle& circle)
{
	Vector2D point = rect.center;


	if (circle.center.x > rect.center.x)
	{
		point.x = min(rect.right, circle.center.x);
	}
	else
	{
		point.x = max(rect.left, circle.center.x);
	}

	if (circle.center.y > rect.center.y)
	{
		point.y = min(rect.top, circle.center.y);
	}
	else
	{
		point.y = max(rect.bottom, circle.center.y);
	}

	return PointCircleIntersection(point, circle);
}

bool MovingPointLineIntersection(const LineSegment& staticLine, const LineSegment& movingPoint, Vector2D& intersection, float& t)
{
	Vector2D velocity = movingPoint.end - movingPoint.start;
	Vector2D normal = staticLine.normal;

	if (velocity.MagnitudeSquared() == 0 || velocity.DotProduct(normal) == 0)
	{
		return false;
	}

	t = (normal.DotProduct(staticLine.start) - normal.DotProduct(movingPoint.start)) / normal.DotProduct(velocity);

	if (t < 0 || t > 1)
	{
		return false;
	}

	float x = movingPoint.start.x + (t * velocity.x);
	float y = movingPoint.start.y + (t * velocity.y);

	intersection = Vector2D(x, y);

	if (!PointIsBetweenLines(intersection, staticLine.start, staticLine.end, staticLine.direction))
	{
		return false;
	}

	return true;

}

void MovingPointLineReflection(Transform& transform, Physics& physics, const LineSegment& staticLine, 
							   const LineSegment& movingPoint, const Vector2D& intersection)
{
	Vector2D tempEnd = movingPoint.end;

	if (AlmostEqual(movingPoint.end, intersection))
	{
		tempEnd += movingPoint.direction * 0.001f;
	}

	Vector2D newPos = ReflectPointOverLine(tempEnd, staticLine);
	transform.SetTranslation(newPos);

	Vector2D newVel = (newPos - intersection).Normalized() * physics.GetVelocity().Magnitude();
	physics.SetVelocity(newVel);

	float newAng = atan2(newVel.Normalized().y, newVel.Normalized().x);
	transform.SetRotation(newAng);
}


bool PointIsBetweenLines(const Vector2D& point, const Vector2D& firstLine, const Vector2D& secondLine, const Vector2D& normal)
{
	float dist1 = normal.DotProduct(point);
	float dist2 = normal.DotProduct(firstLine);
	float dist3 = normal.DotProduct(secondLine);

	if (dist1 < dist2 && dist1 < dist3)
	{
		return false;
	}

	if (dist1 > dist2 && dist1 > dist3)
	{
		return false;
	}

	return true;
}

Vector2D ReflectPointOverLine(const Vector2D& point, const LineSegment& line)
{
	Vector2D originPoint = point - line.start;

	Vector2D reflectedPoint = originPoint - 2 * (originPoint.DotProduct(line.normal)) * line.normal;

	reflectedPoint += line.start;

	return reflectedPoint;
}