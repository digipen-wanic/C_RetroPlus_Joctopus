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
#include "ItemMovement.h"
#include "ColliderRectangle.h"

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

		meshText = CreateQuadMesh(Vector2D(1.0f / 6.0f, 1.0f / 6.0f), Vector2D(0.5f, 0.5f));
		textureText = Texture::CreateTextureFromFile("NumberLetterSpriteSheet.png");
		spriteSourceText = new SpriteSource(6, 6, textureText);

		meshFrog = CreateQuadMesh(Vector2D(1.0f, 1.0f / 2.0f), Vector2D(0.5f, 0.5f));
		Texture* textureFrog = Texture::CreateTextureFromFile("PlayerFrog.png");
		spriteSourceFrog = new SpriteSource(1, 2, textureFrog);

		meshFloat = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		Texture* textureFloat = Texture::CreateTextureFromFile("BrownSquare.png");
		spriteSourceFloat = new SpriteSource(1, 1, textureFloat);

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
		GameObject* text2 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);

		text->GetComponent<SpriteText>()->SetString("ACEGHIK");
		text->GetComponent<SpriteText>()->SetAlignment(LEFT);
		GetSpace()->GetObjectManager().AddObject(*text);

		text2->GetComponent<SpriteText>()->SetString("MNOPRSTY");
		text2->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text2->GetComponent<Transform>()->SetTranslation(Vector2D(-150.0f, 150.0f));
		GetSpace()->GetObjectManager().AddObject(*text2);

		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Frog", meshFrog, spriteSourceFrog));

		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateShip(meshShip));
		//musicChannel = soundManager->PlaySound("Asteroid Field");

		//Car type one
		GameObject* car1_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car1_1->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car1_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_1);

		GameObject* car1_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car1_2->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car1_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_2);

		GameObject* car1_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car1_3->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car1_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -250));
		GetSpace()->GetObjectManager().AddObject(*car1_3);

		//Car type two
		GameObject* car2_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_1->GetComponent<Transform>()->SetTranslation(Vector2D(-10, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_1);

		GameObject* car2_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-190, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_2);

		GameObject* car2_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-370, -200));
		GetSpace()->GetObjectManager().AddObject(*car2_3);

		//Car type three
		GameObject* car3_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_1);

		GameObject* car3_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_2);

		GameObject* car3_3 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -150));
		GetSpace()->GetObjectManager().AddObject(*car3_3);

		//Car type four
		GameObject* car4_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		car4_1->GetComponent<Transform>()->SetTranslation(Vector2D(-100, -100));
		GetSpace()->GetObjectManager().AddObject(*car4_1);

		//Truck
		GameObject* truck_1 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_1->GetComponent<Transform>()->SetTranslation(Vector2D(50, -50));
		truck_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_1);

		GameObject* truck_2 = GameObjectFactory::GetInstance().CreateObject("Car", meshFrog);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_2->GetComponent<Transform>()->SetTranslation(Vector2D(290, -50));
		truck_2->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_2);

		// Floats
		GameObject* float_1 = GameObjectFactory::GetInstance().CreateObject("Float", meshFloat, spriteSourceFloat);
		float_1->GetComponent<Behaviors::ItemMovement>()->SetLeft(false);
		float_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		float_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 50));
		float_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		float_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*float_1);

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
		delete meshFloat;
		delete spriteSourceFloat;
		//soundManager->Shutdown();
		std::cout << "Level1::Unload" << std::endl;
	}
}