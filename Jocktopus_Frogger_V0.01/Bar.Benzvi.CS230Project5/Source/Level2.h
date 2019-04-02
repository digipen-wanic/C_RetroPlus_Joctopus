//------------------------------------------------------------------------------
//
// File Name:	Level2.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include <Level.h>
#include "SoundManager.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Texture;
class SpriteSource;
class Mesh;
class GameObject;
class Tilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Level2 : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 2.
		Level2();

		// Load the resources associated with Level 2.
		void Load() override;

		// Initialize the memory associated with Level 2.
		void Initialize() override;

		// Update Level 2.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with Level 2.
		void Unload() override;

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Monkey
		Mesh* meshMonkey;
		Texture* textureMonkey;
    SpriteSource* spriteSourceMonkey;
		unsigned columnsMonkey;
		unsigned rowsMonkey;

		// Tilemap
		Tilemap* dataMap;
		Texture* textureMap;
    SpriteSource* spriteSourceMap;
		Mesh* meshMap;
		unsigned columnsMap;
		unsigned rowsMap;

		/////////////////////////////////////////////////////////////////////////////
		Mesh* mesh1x1;
		Mesh* mesh1x2;
		Mesh* mesh2x2;

		SpriteSource* spriteSourceDeadFrog;
		SpriteSource* spriteSourceFrog;
		SpriteSource* spriteSourceLogSmall;
		SpriteSource* spriteSourceLogMedium;
		SpriteSource* spriteSourceLogLarge;
		//SpriteSource* spriteSourceTurtle;
		SpriteSource* spriteSourceCar1;
		SpriteSource* spriteSourceCar2;
		SpriteSource* spriteSourceCar3;
		SpriteSource* spriteSourceCar4;
		SpriteSource* spriteSourceCar5;
		SpriteSource* spriteSourceWinFrog;

		Mesh* meshText;
		Texture* textureText;
		SpriteSource* spriteSourceText;

		// Game Variables
		GameObject* currFrog;
		GameObject* scoreText;
		GameObject* timerObject;
		int lives;
		float timer;
		bool lost;

		// Sounds
		SoundManager* soundManager;

		// Title
		static const unsigned titleStringLength = 20;
		char windowTitle[titleStringLength];
	};
}

//----------------------------------------------------------------------------
