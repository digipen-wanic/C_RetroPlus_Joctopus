//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Animation.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "GameObject.h"

Animation::Animation()
	: Component("Animation"), frameIndex(0), frameCount(0), frameStart(0), frameDelay(0.0f), frameDuration(0.0f), 
	  isRunning(false), isLooping(false), isDone(false)
{
}

Component* Animation::Clone() const
{
	return new Animation(*this);
}

void Animation::Initialize()
{
	sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
}

void Animation::Play(unsigned frameStart_, unsigned frameCount_, float frameDuration_, bool isLooping_)
{
	frameIndex = frameStart_;
	frameCount = frameCount_;
	frameStart = frameStart_;
	frameDuration = frameDuration_;
	frameDelay = frameDuration_;
	isLooping = isLooping_;
	isRunning = true;
	isDone = false;

}

void Animation::Update(float dt)
{

	if (isRunning)
	{
		frameDelay -= dt;

		isDone = false;

		if (frameDelay <= 0)
		{
			frameDelay = frameDuration;

			frameIndex += 1;

			if (frameIndex >= frameCount && isLooping)
			{
				isDone = true;
				frameIndex = 0;
			}
			else if(frameIndex >= frameCount)
			{
				isRunning = false;
				isDone = true;
				return;
			}

			sprite->SetFrame(frameIndex);
		}
	}
}

bool Animation::IsDone() const
{
	return isDone;
}