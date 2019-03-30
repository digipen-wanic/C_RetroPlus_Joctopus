//------------------------------------------------------------------------------
//
// File Name:	TurtleMovement.h
// Author(s):	Freddy Martin
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#pragma once
#include "stdafx.h"
#include <Component.h>

class SpriteSource;

namespace Behaviors
{
	enum TurtlePhase
	{
		Floating,
		Sinking,
		Sunk
	};
	class TurtleMovement : public Component
	{
	public:
		// Constructor
		TurtleMovement();

		// Returns clone of the component
		Component* Clone() const override;

		// Runs every frame
		void Update(float dt) override;

		// Runs whenever the object is created
		void Shutdown() override;

		// Loads from an object file
		void Deserialize(Parser& parser);

		// Saves to an object file
		void Serialize(Parser& parser) const;

		// Sets the flipAnimation
		void SetFlipAnimation(SpriteSource* flipAnimation_);

		// Changes the turtle's current phase
		void ChangePhase();

		// Returns true if the turtle can be stood on
		bool IsStandable();
	private:
		// Keeps track of phase changes
		float timer;
		// Flip Animation
		SpriteSource* flipAnimation;
		// The starting sprite
		SpriteSource* startSprite;
		// The current phase of the turtle
		TurtlePhase currPhase;
	};
}