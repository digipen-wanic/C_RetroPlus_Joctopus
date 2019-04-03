//------------------------------------------------------------------------------
//
// File Name:	Level1.h
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

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Mesh;
class Texture;
class SpriteSource;
class GameObject;
class SoundManager;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class Level1 : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 1.
		Level1();

		// Load the resources associated with Level 1.
		void Load() override;

		// Initialize the memory associated with Level 1.
		void Initialize() override;
		
		// Update the Level 1.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with Level 1.
		void Unload() override;

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Meshes

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
		SpriteSource* spriteSourceWinFrog2;
		SpriteSource* spriteSourceBackground;
		SpriteSource* spriteSourceDrownFrog;
		SpriteSource* spriteSourceCombinedFrog;
		SpriteSource* spriteSourceFly;

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
		Texture* textureWinFrog2;
		Texture* textureDrownFrog;
		Texture* textureTurtleFloat2;
		Texture* textureTurtleFloat3;
		Texture* textureTurtleSink2;
		Texture* textureTurtleSink3;
		Texture* textureCombinedFrog;
		Texture* textureFly;

		// Game Variables
		GameObject* currFrog;
		GameObject* scoreText;
		GameObject* highScoreText;
		GameObject* timerObject;
		GameObject* FrogLife1;
		GameObject* FrogLife2;
		GameObject* currFly;
		int lives;
		float timer;
		float winLoseTimer;
		float flySpawnTimer;
		float flyAliveTimer;
		bool winLoseSequenceInit;
		bool lost;
		bool won;
		std::vector<GameObject*> winSlots;

		// Sounds
		SoundManager* soundManager;

		// Title
		static const unsigned titleStringLength = 20;
		char windowTitle[titleStringLength];
	};
}

//----------------------------------------------------------------------------
