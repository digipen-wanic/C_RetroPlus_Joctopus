//------------------------------------------------------------------------------
//
// File Name:	TurtleMovement.cpp
// Author(s):	Freddy Martin
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

namespace Behaviors
{
	TurtleMovement::TurtleMovement()
		:Component("TurtleMovement"), currPhase(Floating)
	{
		startSprite = GetOwner()->GetComponent<Sprite>()->GetSpriteSource();
	}
	Component * TurtleMovement::Clone() const
	{
		return new TurtleMovement(*this);
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
	void TurtleMovement::Deserialize(Parser & parser)
	{
	}
	void TurtleMovement::Serialize(Parser & parser) const
	{
	}
	void TurtleMovement::SetFlipAnimation(SpriteSource * flipAnimation_)
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
		if (currPhase == Floating)
		{
			currPhase = Sinking;
			spriteComp->SetSpriteSource(flipAnimation);
			spriteComp->SetFrame(0);
		}
		else if (currPhase == Sinking)
		{
			currPhase = Sunk;
			spriteComp->SetSpriteSource(startSprite);
			spriteComp->SetFrame(0);
			spriteComp->SetColor(Color(spriteComp->GetColor().r, spriteComp->GetColor().g, spriteComp->GetColor().b, 0));
		}
		else if (currPhase == Sunk)
		{
			currPhase = Floating;
			spriteComp->SetColor(Color(spriteComp->GetColor().r, spriteComp->GetColor().g, spriteComp->GetColor().b, 1));
		}
	}
	bool TurtleMovement::IsStandable()
	{
		return currPhase != Sunk;
	}
}