//------------------------------------------------------------------------------
//
// File Name:	Physics.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "Physics.h"
#include "Transform.h"
#include "GameObject.h"
#include "Parser.h"


Physics::Physics()
	: Component("Physics"), velocity(Vector2D(0.0f, 0.0f)), angularVelocity(0.0f), inverseMass(1.0f), forcesSum(Vector2D(0.0f, 0.0f)), 
	  acceleration(Vector2D(0.0f, 0.0f)), oldTranslation(Vector2D(0.0f, 0.0f))
{
}

Component* Physics::Clone() const
{
	return new Physics(*this);
}

void Physics::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
}

void Physics::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
	
	acceleration = forcesSum * inverseMass;

	forcesSum.x = 0.0f;
	forcesSum.y = 0.0f;
}

void Physics::FixedUpdate(float dt)
{
	velocity += acceleration * dt;

	oldTranslation = transform->GetTranslation();

	transform->SetTranslation(oldTranslation + (velocity * dt));
	transform->SetRotation(transform->GetRotation() + (angularVelocity * dt));

}

void Physics::SetVelocity(const Vector2D& velocity_)
{
	velocity = velocity_;
}

const Vector2D& Physics::GetVelocity() const
{
	return velocity;
}

void Physics::SetAngularVelocity(float velocity_)
{
	angularVelocity = velocity_;
}

float Physics::GetAngularVelocity() const
{
	return angularVelocity;
}

void Physics::SetMass(float mass)
{
	inverseMass = 1.0f / mass;
}

void Physics::AddForce(const Vector2D& force)
{
	forcesSum += force;
}

const Vector2D& Physics::GetAcceleration() const
{
	return acceleration;
}

const Vector2D& Physics::GetOldTranslation() const
{
	return oldTranslation;
}

// Loads object data from a file.
void Physics::Deserialize(Parser& parser)
{
	parser.ReadVariable("acceleration", acceleration);
	parser.ReadVariable("velocity", velocity);
	parser.ReadVariable("angularVelocity", angularVelocity);
	parser.ReadVariable("mass", inverseMass);
	inverseMass = 1 / inverseMass;
}

// Saves object data to a file.
void Physics::Serialize(Parser& parser) const
{
	parser.WriteVariable("acceleration", acceleration);
	parser.WriteVariable("velocity", velocity);
	parser.WriteVariable("angularVelocity", angularVelocity);
	parser.WriteVariable("mass", 1 / inverseMass);
}