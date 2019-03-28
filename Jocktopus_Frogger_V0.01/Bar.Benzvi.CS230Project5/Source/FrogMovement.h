//------------------------------------------------------------------------------
//
// File Name:	FrogMovement.h
// Author(s):	Freddy Martin
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#pragma once
#include "stdafx.h"
#include <SpriteSource.h>
#include <Component.h>
#include <Vector2D.h>

namespace Behaviors
{
	class FrogMovement : public Component
	{
	public:
		FrogMovement(float speed = 50, int walkFrames = 2);
		Component* Clone() const override;
		void Initialize() override;
		void Update(float dt) override;
		friend void FrogCollisionHandler(GameObject& object, GameObject& other);
		void Deserialize(Parser& parser);
		void Serialize(Parser& parser) const;
	private:
		float speed;
		int canWalk;
		int walkFrames;
	};
}