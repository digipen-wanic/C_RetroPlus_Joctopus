//------------------------------------------------------------------------------
//
// File Name:	MainMenu.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MainMenu.h"
#include "GameObject.h"
#include "Level1.h"
#include "SpriteSource.h"
#include "Sprite.h"
#include "MeshHelper.h"
#include "Texture.h"
#include "GameObjectFactory.h"
#include "SpriteText.h"
#include "GameObjectManager.h"
#include "Space.h"
#include "Transform.h"
#include "Mesh.h"
#include "FrogMovement.h"
#include "Input.h"

namespace Levels
{
	MainMenu::MainMenu()
		: Level("MainMenu"), currAlpha(1.0f), addingAlpha(false)
	{
	}

	void MainMenu::Load()
	{
		mesh1x1 = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		meshText = CreateQuadMesh(Vector2D(1.0f / 6.0f, 1.0f / 6.0f), Vector2D(0.5f, 0.5f));

		textureTitle = Texture::CreateTextureFromFile("UITitle.png");
		spriteSourceTitle = new SpriteSource(1, 1, textureTitle);

		textureBackground = Texture::CreateTextureFromFile("Background.png");
		spriteSourceBackground = new SpriteSource(1, 1, textureBackground);

		textureText = Texture::CreateTextureFromFile("NumberLetterSpriteSheet.png");
		spriteSourceText = new SpriteSource(6, 6, textureText);
	}

	void MainMenu::Initialize()
	{
		GameObject* background = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh1x1, spriteSourceBackground);
		background->GetComponent<Transform>()->SetScale(Vector2D(672, 768));
		GetSpace()->GetObjectManager().AddObject(*background);

		GameObject* text1 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text1->GetComponent<SpriteText>()->SetString("SCORE");
		text1->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text1->GetComponent<Transform>()->SetTranslation(Vector2D(-320.0f, 368.0f));
		GetSpace()->GetObjectManager().AddObject(*text1);

		GameObject* text2 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text2->GetComponent<SpriteText>()->SetString("0");
		text2->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text2->GetComponent<Transform>()->SetScale(Vector2D(16.0f, 18.0f));
		GetSpace()->GetObjectManager().AddObject(*text2);

		GameObject* text3 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text3->GetComponent<SpriteText>()->SetString("HIGH SCORE");
		text3->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text3->GetComponent<Transform>()->SetTranslation(Vector2D(-64.0f, 368.0f));
		GetSpace()->GetObjectManager().AddObject(*text3);

		highScoreText = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		highScoreText->GetComponent<SpriteText>()->SetString(std::to_string(Behaviors::FrogMovement::GetHighScore()));
		highScoreText->GetComponent<SpriteText>()->SetAlignment(LEFT);
		highScoreText->GetComponent<Transform>()->SetScale(Vector2D(16.0f, 18.0f));
		highScoreText->GetComponent<Transform>()->SetTranslation(Vector2D(-64.0f, 344.0f));
		GetSpace()->GetObjectManager().AddObject(*highScoreText);

		startText = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		startText->GetComponent<SpriteText>()->SetString("PRESS 1 TO START");
		startText->GetComponent<Transform>()->SetTranslation(Vector2D(0.0f, -100.0f));
		GetSpace()->GetObjectManager().AddObject(*startText);

		GameObject* title = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh1x1, spriteSourceTitle);
		title->GetComponent<Transform>()->SetScale(Vector2D(768.0f, 250.0f));
		title->GetComponent<Transform>()->SetTranslation(Vector2D(96.0f, 24.0f));
		GetSpace()->GetObjectManager().AddObject(*title);



	}

	void MainMenu::Update(float dt)
	{
		if (addingAlpha)
		{
			currAlpha += dt;
			if (currAlpha >= 1.0f)
			{
				currAlpha = 1.0f;
				addingAlpha = false;
			}
		}
		else
		{
			currAlpha -= dt;
			if (currAlpha <= 0.0f)
			{
				currAlpha = 0.0f;
				addingAlpha = true;
			}
		}

		startText->GetComponent<Sprite>()->SetAlpha(currAlpha);

		if (Input::GetInstance().CheckTriggered('1'))
		{
			GetSpace()->SetLevel<Level1>();
		}

	}




	void MainMenu::Unload()
	{
		delete mesh1x1;
		delete meshText;
		delete textureTitle;
		delete textureBackground;
		delete textureText;
		delete spriteSourceTitle;
		delete spriteSourceBackground;
		delete spriteSourceText;
	}

}