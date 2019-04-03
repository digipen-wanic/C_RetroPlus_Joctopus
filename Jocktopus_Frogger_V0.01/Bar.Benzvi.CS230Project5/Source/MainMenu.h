//------------------------------------------------------------------------------
//
// File Name:	MainMenu.h
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Level.h"

class Mesh;
class Texture;
class SpriteSource;
class GameObject;

namespace Levels
{
	class MainMenu : public Level
	{
	public:
		
		MainMenu();

		void Load() override;

		void Initialize() override;

		void Update(float dt) override;

		void Unload() override;

	private:

		//Meshes, Textures, Spritesources
		Mesh* mesh1x1;
		Mesh* meshText;

		SpriteSource* spriteSourceTitle;
		SpriteSource* spriteSourceBackground;
		SpriteSource* spriteSourceText;

		Texture* textureTitle;
		Texture* textureBackground;
		Texture* textureText;

		//Text variables

		GameObject* startText;
		GameObject* highScoreText;

		float currAlpha;
		bool addingAlpha;


	};
}