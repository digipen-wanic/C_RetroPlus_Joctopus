//------------------------------------------------------------------------------
//
// File Name:	TurtleMovement.cpp
// Author(s):	Freddy Martin, Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "TurtleMovement.h"
#include <GameObject.h>
#include <Sprite.h>
#include <Animation.h>
#include "SpriteSource.h"

namespace Behaviors
{
	TurtleMovement::TurtleMovement()
		:Component("TurtleMovement"), currPhase(Floating), flipAnimation(nullptr)
	{
		
	}
	Component * TurtleMovement::Clone() const
	{
		return new TurtleMovement(*this);
	}

	void TurtleMovement::Initialize()
	{
		startSprite = GetOwner()->GetComponent<Sprite>()->GetSpriteSource();
		GetOwner()->GetComponent<Animation>()->Play(0, 3, 0.5f, true);
	}

	void TurtleMovement::Update(float dt)
	{
		timer += dt;
		if (timer > 1)
		{
			timer = 0;
			ChangePhase();
		}
	}
	void TurtleMovement::Shutdown()
	{
		if (flipAnimation != nullptr)
		{
			delete flipAnimation;
		}
	}
	void TurtleMovement::Deserialize(Parser& parser)
	{
		UNREFERENCED_PARAMETER(parser);
	}
	void TurtleMovement::Serialize(Parser& parser) const
	{
		UNREFERENCED_PARAMETER(parser);
	}
	void TurtleMovement::SetFlipAnimation(SpriteSource* flipAnimation_)
	{
		if (flipAnimation != nullptr)
		{
			delete flipAnimation;
		}
		flipAnimation = flipAnimation_;
	}
	void TurtleMovement::ChangePhase()
	{
		Sprite* spriteComp = GetOwner()->GetComponent<Sprite>();
		Animation* animationComp = GetOwner()->GetComponent<Animation>();
		if (animationComp == nullptr)
		{
			return;
		}
		if (currPhase == Floating)
		{
			currPhase = Sinking;
			spriteComp->SetSpriteSource(flipAnimation);
			animationComp->Play(0, 2, 0.5f, true);
		}
		else if (currPhase == Sinking)
		{
			currPhase = Sunk;
			spriteComp->SetSpriteSource(startSprite);
			spriteComp->SetAlpha(0);
		}
		else if (currPhase == Sunk)
		{
			currPhase = Floating;
			spriteComp->SetAlpha(1);
			animationComp->Play(0, 3, 0.33f, true);
		}
	}
	bool TurtleMovement::IsStandable()
	{
		return currPhase != Sunk;
	}
}