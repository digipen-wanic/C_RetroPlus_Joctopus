//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Level1.h"
#include "Level2.h"
#include "Engine.h"
#include "Space.h"
#include "MeshHelper.h"
#include "Color.h"
#include "Sprite.h"
#include "Mesh.h"
#include "Input.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"
#include "Archetypes.h"
#include "GameObjectManager.h"
#include "Level3.h"
#include "SoundManager.h"
#include <fmod.hpp>
#include "Parser.h"
#include "Omega.h"
#include "GameObjectFactory.h"
#include "Texture.h"
#include "SpriteSource.h"
#include "SpriteText.h"

namespace Levels
{
	Level1::Level1()
		: Level("Level1"), meshShip(nullptr), meshFrog(nullptr)
	{

	}

	void Level1::Load()
	{

/*		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->AddEffect("teleport.wav");
		soundManager->AddMusic("Asteroid_Field.mp3");

		soundManager->AddBank("Master Bank.strings.bank");
		soundManager->AddBank("Master Bank.bank");*/

		//meshShip = CreateTriangleMesh(Colors::Red, Colors::Blue, Colors::Green);
		//meshBullet = CreateTriangleMesh(Colors::Aqua, Colors::Grey, Colors::LightBlue);

		meshText = CreateQuadMesh(Vector2D(1.0f / 2.0f, 1.0f / 5.0f), Vector2D(0.5f, 0.5f));
		textureText = Texture::CreateTextureFromFile("Jocktopus_TextSpritesheet_Test.png");
		spriteSourceText = new SpriteSource(2, 5, textureText);

		meshFrog = CreateQuadMesh(Vector2D(1.0f / 2.0f, 1), Vector2D(0.5f, 0.5f));
		Texture* textureFrog = Texture::CreateTextureFromFile("FrogTest.png");
		spriteSourceFrog = new SpriteSource(2, 1, textureFrog);

		//GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet", meshBullet));

		//GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet));

		std::cout << "Level1::Load" << std::endl;
	}

	void Level1::Initialize()
	{

		//GameObject* ship = GameObjectFactory::GetInstance().CreateObject("PlayerShip", meshShip);

		//ship->GetComponent<Transform>()->SetRotation(3.14f);

		//GetSpace()->GetObjectManager().AddObject(*ship);

		GameObject* text = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);

		text->GetComponent<SpriteText>()->SetString("0123456789");

		GetSpace()->GetObjectManager().AddObject(*text);

		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Frog", meshFrog, spriteSourceFrog));

		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateShip(meshShip));
		//musicChannel = soundManager->PlaySound("Asteroid Field");

		std::cout << "Level1::Initialize" << std::endl;
	}

	void Level1::Update(float dt)
	{

		unsigned bulletCount = GetSpace()->GetObjectManager().GetObjectCount("Bullet");

		sprintf_s(windowTitle, "Bullets: %u", bulletCount);

		UNREFERENCED_PARAMETER(dt);

		if (Input::GetInstance().CheckTriggered('1'))
		{
			GetSpace()->SetLevel<Levels::Level1>();
		}
		else if (Input::GetInstance().CheckTriggered('2'))
		{
			GetSpace()->SetLevel<Levels::Level2>();
		}
		else if (Input::GetInstance().CheckTriggered('3'))
		{
			GetSpace()->SetLevel<Levels::Level3>();
		}
		else if (Input::GetInstance().CheckTriggered('4'))
		{
			GetSpace()->SetLevel<Levels::Omega>();
		}

		if (Input::GetInstance().CheckTriggered('T'))
		{
			//soundManager->PlaySound("teleport.wav");
		}

		
	}


	void Level1::Unload()
	{
		Parser parse("ParseTest.txt", std::fstream::out);
		parse.BeginScope();
		parse.BeginScope();
		
		parse.WriteVariable("Bar", 18.0f);

		parse.WriteValue(false);
		parse.EndScope();
		parse.EndScope();

		delete meshShip;
		delete meshFrog;
		delete spriteSourceFrog;
		//soundManager->Shutdown();
		std::cout << "Level1::Unload" << std::endl;
	}
}