//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Level2.h"
#include "Engine.h"
#include "Space.h"
#include "Mesh.h"
#include "MeshHelper.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Animation.h"
#include "Input.h"
#include "Level1.h"
#include "Transform.h"
#include "Physics.h"
#include "GameObject.h"
#include "Level3.h"
#include "Tilemap.h"
#include "GameObjectFactory.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"
#include "Omega.h"

namespace Levels
{
	Level2::Level2()
		: Level("Level2"), columnsMonkey(3), rowsMonkey(5), columnsMap(4), rowsMap(3)
	{

	}

	void Level2::Load()
	{
		meshMonkey = CreateQuadMesh(Vector2D(1.0f / 3.0f, 1.0f / 5.0f), Vector2D(0.5, 0.5));
		textureMonkey = Texture::CreateTextureFromFile("Monkey.png");
		spriteSourceMonkey = new SpriteSource(columnsMonkey, rowsMonkey, textureMonkey);

		meshMap = CreateQuadMesh(Vector2D(1.0f / columnsMap, 1.0f / rowsMap), Vector2D(0.5f, 0.5f));
		textureMap = Texture::CreateTextureFromFile("Tilemap.png");
		spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);
		dataMap = Tilemap::CreateTilemapFromFile("level2.txt");

		if (dataMap == nullptr)
		{
			std::cout << "Error loading map" << std::endl;
		}

		std::cout << "Level2::Load" << std::endl;
	}

	void Level2::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;
		
		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Monkey", meshMonkey, spriteSourceMonkey));
		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateMonkey());

		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap));
		GameObject* tileMap = GameObjectFactory::GetInstance().CreateObject("Tilemap", meshMap, spriteSourceMap);
		static_cast<SpriteTilemap*>(tileMap->GetComponent("Sprite"))->SetTilemap(dataMap);
		static_cast<ColliderTilemap*>(tileMap->GetComponent("Collider"))->SetTilemap(dataMap);

		GetSpace()->GetObjectManager().AddObject(*tileMap);


		static_cast<Animation*>(GetSpace()->GetObjectManager().GetObjectByName("Monkey")->GetComponent("Animation"))->Play(0, 8, 0.2f, true);
	}

	void Level2::Update(float dt)
	{

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
	}


	void Level2::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;

		delete dataMap;
		delete textureMonkey;
		delete spriteSourceMonkey;
		delete meshMonkey;
		delete textureMap;
		delete spriteSourceMap;
		delete meshMap;
	}
}

