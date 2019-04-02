//------------------------------------------------------------------------------
//
// File Name:	FrogMovement.h
// Author(s):	Freddy Martin, Bar Ben-zvi
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

class SoundManager;
class Mesh;
class SpriteSource;

namespace Behaviors
{
	

	class FrogMovement : public Component
	{
	public:
		// Constructor
		FrogMovement(float speed = 48, int walkFrames = 4, float deathTime = 2);

		// Returns clone of the component
		Component* Clone() const override;

		// Runs when the object is created
		void Initialize() override;

		// Runs every frame
		void Update(float dt) override;

		// Runs every 1/60 seconds
		void FixedUpdate(float dt) override;

		// Runs whenever the object is created
		void Shutdown() override;

		// Runs whenever a collision is detected
		friend void FrogCollisionHandler(GameObject& object, GameObject& other);

		// Loads from an object file
		void Deserialize(Parser& parser);

		// Saves to an object file
		void Serialize(Parser& parser) const;

		// Starts the death sequence of the frog
		void InitDeathSequence();

		// Sets the death animation of the frog
		void SetDeathAnimations(SpriteSource* deathAnimation_, SpriteSource* drownAnimation);

		//Gets the static score variable
		int GetScore() const;

		//Gets the current amount of time until the current frog dies
		float GetTimer() const;

		static int GetLives();

		void SetWinSprite(Mesh* mesh, SpriteSource* spriteSource);

	private:
		// Amount the frog moves
		float speed;

		// Time until restart when the player dies
		float deathTime;

		// Timer that counts until the player dies
		float timer;

		float loseTimer;

		// 0 if can walk
		int canWalk;

		// Amount of frames between moves that the player can move
		int walkFrames;

		// The furthest forward the player has gone
		static int furthestForward;

		// How far forward the player currently is
		int currentForward;

		// If the player is dying
		bool dying;

		// If the player is on a float
		bool onFloat;

		// Animation to play when the frog dies
		SpriteSource* deathAnimation;
		SpriteSource* drownAnimation;

		// WinSpriteStuff
		Mesh* winMesh;
		SpriteSource* winSpriteSource;

		SoundManager* soundManager;

		static int score;
		static int lives;

		bool waterDeathActive;
	};
}