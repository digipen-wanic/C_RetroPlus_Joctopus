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
#include "ItemMovement.h"
#include "ColliderRectangle.h"
#include "PurpleFrogMovement.h"


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
		
		//GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Monkey", meshMonkey, spriteSourceMonkey));
		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateMonkey());

		//Car type one
		GameObject* car1_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_1);

		GameObject* car1_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_2);

		GameObject* car1_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_3);

		//Car type two
		GameObject* car2_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_1->GetComponent<Transform>()->SetTranslation(Vector2D(-10, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_1);

		GameObject* car2_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-190, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_2);

		GameObject* car2_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-370, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_3);

		//Car type three
		GameObject* car3_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_1);

		GameObject* car3_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_2);

		GameObject* car3_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_3);

		//Car type four
		GameObject* car4_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		car4_1->GetComponent<Transform>()->SetTranslation(Vector2D(-100, -100));
		GetSpace()->GetObjectManager().AddObject(*car4_1);

		//Truck
		GameObject* truck_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_1->GetComponent<Transform>()->SetTranslation(Vector2D(50, -50));
		truck_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_1);

		GameObject* truck_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshMonkey);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_2->GetComponent<Transform>()->SetTranslation(Vector2D(290, -50));
		truck_2->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_2);

		// Turtle
		GameObject* turtle_1 = GameObjectFactory::GetInstance().CreateObject("Float", meshMonkey, spriteSourceMonkey);
		turtle_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 50));
		turtle_1->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		turtle_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1);

		GameObject* turtle_2 = GameObjectFactory::GetInstance().CreateObject("Float", meshMonkey, spriteSourceMonkey);
		turtle_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2->GetComponent<Transform>()->SetTranslation(Vector2D(260, 200));
		turtle_2->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		turtle_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2);
		
		// Log
		GameObject* log_1 = GameObjectFactory::GetInstance().CreateObject("Float", meshMonkey, spriteSourceMonkey);
		log_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(45);
		log_1->GetComponent<Transform>()->SetTranslation(Vector2D(250, 100));
		log_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		log_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*log_1);

		GameObject* log_2 = GameObjectFactory::GetInstance().CreateObject("Float", meshMonkey, spriteSourceMonkey);
		log_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2->GetComponent<Transform>()->SetTranslation(Vector2D(290, 150));
		log_2->GetComponent<Transform>()->SetScale(Vector2D(120, 30));
		log_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(60, 15));
		GetSpace()->GetObjectManager().AddObject(*log_2);

		GameObject* log_3 = GameObjectFactory::GetInstance().CreateObject("Float", meshMonkey, spriteSourceMonkey);
		log_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		log_3->GetComponent<Transform>()->SetTranslation(Vector2D(290, 250));
		log_3->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		log_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*log_3);

		// PFrog
		GameObject* PFrog = GameObjectFactory::GetInstance().CreateObject("PFrog", meshMonkey, spriteSourceMonkey);
		PFrog->GetComponent<Transform>()->SetTranslation(Vector2D(235, 100));
		GetSpace()->GetObjectManager().AddObject(*PFrog);



		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap));
		GameObject* tileMap = GameObjectFactory::GetInstance().CreateObject("Tilemap", meshMap, spriteSourceMap);
		static_cast<SpriteTilemap*>(tileMap->GetComponent("Sprite"))->SetTilemap(dataMap);
		static_cast<ColliderTilemap*>(tileMap->GetComponent("Collider"))->SetTilemap(dataMap);

		//GetSpace()->GetObjectManager().AddObject(*tileMap);


		//static_cast<Animation*>(GetSpace()->GetObjectManager().GetObjectByName("Monkey")->GetComponent("Animation"))->Play(0, 8, 0.2f, true);
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

