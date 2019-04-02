//------------------------------------------------------------------------------
//
// File Name:	Level2.h
// Author(s):	Jeremy Kings (j.kings), Kyle
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
		Mesh* mesh1x3;

		SpriteSource* spriteSourceDeadFrog;
		SpriteSource* spriteSourceFrog;
		SpriteSource* spriteSourcePFrog;
		SpriteSource* spriteSourceLogSmall;
		SpriteSource* spriteSourceLogMedium;
		SpriteSource* spriteSourceLogLarge;
		SpriteSource* spriteSourceTurtleFloat2;
		SpriteSource* spriteSourceTurtleFloat3;
		SpriteSource* spriteSourceTurtleSink2;
		SpriteSource* spriteSourceTurtleSink3;
		SpriteSource* spriteSourceCar1;
		SpriteSource* spriteSourceCar2;
		SpriteSource* spriteSourceCar3;
		SpriteSource* spriteSourceCar4;
		SpriteSource* spriteSourceCar5;
		SpriteSource* spriteSourceWinFrog;
		SpriteSource* spriteSourceBackground;
		SpriteSource* spriteSourceDrownFrog;

		Mesh* meshText;
		Texture* textureText;
		SpriteSource* spriteSourceText;

		// Textures
		Texture* textureBackground;
		Texture* textureDeadFrog;
		Texture* textureFrog;
		Texture* texturePFrog;
		Texture* textureLogLarge;
		Texture* textureLogMedium;
		Texture* textureLogSmall;
		Texture* textureCar1;
		Texture* textureCar2;
		Texture* textureCar3;
		Texture* textureCar4;
		Texture* textureCar5;
		Texture* textureWinFrog;
		Texture* textureDrownFrog;
		Texture* textureTurtleFloat2;
		Texture* textureTurtleFloat3;
		Texture* textureTurtleSink2;
		Texture* textureTurtleSink3;

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
