//------------------------------------------------------------------------------
//
// File Name:	Level1.cpp
// Author(s):	Bar Ben-zvi, Freddy Martin
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
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
#include "FrogMovement.h"
#include "TurtleMovement.h"
#include <Graphics.h>

namespace Levels
{
	Level1::Level1()
		: Level("Level1"), mesh1x1(nullptr), mesh1x2(nullptr), lives(2), timer(40.0f), lost(false)
	{

	}

	void Level1::Load()
	{

		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->SetEffectsVolume(0.5f);
		soundManager->AddEffect("Respawn1.wav");
		soundManager->AddEffect("LoseSong.wav");
		soundManager->AddEffect("WinRibbit.wav");

		//meshShip = CreateTriangleMesh(Colors::Red, Colors::Blue, Colors::Green);
		//meshBullet = CreateTriangleMesh(Colors::Aqua, Colors::Grey, Colors::LightBlue);
		mesh1x1 = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		mesh1x2 = CreateQuadMesh(Vector2D(1.0f, 1.0f / 2.0f), Vector2D(0.5f, 0.5f));
		mesh2x2 = CreateQuadMesh(Vector2D(1.0f / 2.0f, 1.0f / 2.0f), Vector2D(0.5f, 0.5f));
		mesh1x3 = CreateQuadMesh(Vector2D(1.0f, 1.0f / 3.0f), Vector2D(0.5f, 0.5f));

		meshText = CreateQuadMesh(Vector2D(1.0f / 6.0f, 1.0f / 6.0f), Vector2D(0.5f, 0.5f));
		textureText = Texture::CreateTextureFromFile("NumberLetterSpriteSheet.png");
		spriteSourceText = new SpriteSource(6, 6, textureText);

		textureCombinedFrog = Texture::CreateTextureFromFile("YellowPinkFrog.png");
		spriteSourceCombinedFrog = new SpriteSource(2, 2, textureCombinedFrog);

		textureBackground = Texture::CreateTextureFromFile("Background.png");
		spriteSourceBackground = new SpriteSource(1, 1, textureBackground);

		textureDeadFrog = Texture::CreateTextureFromFile("PlayerFrogRoadKill.png");
		spriteSourceDeadFrog = new SpriteSource(2, 2, textureDeadFrog);

		textureDrownFrog = Texture::CreateTextureFromFile("PlayerFrogDrown.png");
		spriteSourceDrownFrog = new SpriteSource(2, 2, textureDrownFrog);

		textureFrog = Texture::CreateTextureFromFile("PlayerFrog.png");
		spriteSourceFrog = new SpriteSource(2, 2, textureFrog);

		texturePFrog = Texture::CreateTextureFromFile("pinkfrog_01.png");
		spriteSourcePFrog = new SpriteSource(2, 2, texturePFrog);

		textureWinFrog = Texture::CreateTextureFromFile("EndFrogSmirk.png");
		spriteSourceWinFrog = new SpriteSource(1, 1, textureWinFrog);

		textureLogLarge = Texture::CreateTextureFromFile("LargeLog.png");
		spriteSourceLogLarge = new SpriteSource(1, 1, textureLogLarge);

		textureLogMedium = Texture::CreateTextureFromFile("MediumLog.png");
		spriteSourceLogMedium = new SpriteSource(1, 1, textureLogMedium);

		textureLogSmall = Texture::CreateTextureFromFile("SmallLog.png");
		spriteSourceLogSmall = new SpriteSource(1, 1, textureLogSmall);

		textureCar1 = Texture::CreateTextureFromFile("yellowcar_01.png");
		spriteSourceCar1 = new SpriteSource(1, 1, textureCar1);

		textureCar2 = Texture::CreateTextureFromFile("dozer_01.png");
		spriteSourceCar2 = new SpriteSource(1, 1, textureCar2);

		textureCar3 = Texture::CreateTextureFromFile("pinkcar_01.png");
		spriteSourceCar3 = new SpriteSource(1, 1, textureCar3);

		textureCar4 = Texture::CreateTextureFromFile("whitecar_01.png");
		spriteSourceCar4 = new SpriteSource(1, 1, textureCar4);

		textureCar5 = Texture::CreateTextureFromFile("truck_01.png");
		spriteSourceCar5 = new SpriteSource(1, 1, textureCar5);

		textureTurtleFloat2 = Texture::CreateTextureFromFile("TurtleSwim2.png");
		spriteSourceTurtleFloat2 = new SpriteSource(1, 3, textureTurtleFloat2);

		textureTurtleFloat3 = Texture::CreateTextureFromFile("TurtleSwim3.png");
		spriteSourceTurtleFloat3 = new SpriteSource(1, 3, textureTurtleFloat3);

		textureTurtleSink2 = Texture::CreateTextureFromFile("TurtleRollDouble.png");
		spriteSourceTurtleSink2 = new SpriteSource(1, 3, textureTurtleSink2);

		textureTurtleSink3 = Texture::CreateTextureFromFile("TurtleRollTriple.png");
		spriteSourceTurtleSink3 = new SpriteSource(1, 3, textureTurtleSink3);

		//GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet", meshBullet));

		//GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet));

		std::cout << "Level1::Load" << std::endl;
	}

	void Level1::Initialize()
	{

		//GameObject* ship = GameObjectFactory::GetInstance().CreateObject("PlayerShip", meshShip);

		//ship->GetComponent<Transform>()->SetRotation(3.14f);

		//GetSpace()->GetObjectManager().AddObject(*ship);

		GameObject* background = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh1x1, spriteSourceBackground);
		background->GetComponent<Transform>()->SetScale(Vector2D(672, 768));
		GetSpace()->GetObjectManager().AddObject(*background);

		FrogLife1 = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh2x2, spriteSourceFrog);
		FrogLife1->GetComponent<Transform>()->SetScale(Vector2D(35, 35));
		FrogLife1->GetComponent<Transform>()->SetTranslation(Vector2D(Graphics::GetInstance().GetScreenWorldDimensions().left + 25, -335));
		GetSpace()->GetObjectManager().AddObject(*FrogLife1);

		FrogLife2 = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh2x2, spriteSourceFrog);
		FrogLife2->GetComponent<Transform>()->SetScale(Vector2D(35, 35));
		FrogLife2->GetComponent<Transform>()->SetTranslation(Vector2D(Graphics::GetInstance().GetScreenWorldDimensions().left + 52, -335));
		GetSpace()->GetObjectManager().AddObject(*FrogLife2);

		GameObject* winSlot1 = GameObjectFactory::GetInstance().CreateObject("WinSlot");
		winSlot1->GetComponent<Transform>()->SetTranslation(Vector2D(-6.0f, 270.0f));
		GetSpace()->GetObjectManager().AddObject(*winSlot1);

		GameObject* winSlot2 = GameObjectFactory::GetInstance().CreateObject("WinSlot");
		winSlot2->GetComponent<Transform>()->SetTranslation(Vector2D(-140.0f, 270.0f));
		GetSpace()->GetObjectManager().AddObject(*winSlot2);

		GameObject* winSlot3 = GameObjectFactory::GetInstance().CreateObject("WinSlot");
		winSlot3->GetComponent<Transform>()->SetTranslation(Vector2D(130.0f, 270.0f));
		GetSpace()->GetObjectManager().AddObject(*winSlot3);

		GameObject* winSlot4 = GameObjectFactory::GetInstance().CreateObject("WinSlot");
		winSlot4->GetComponent<Transform>()->SetTranslation(Vector2D(-276.0f, 270.0f));
		GetSpace()->GetObjectManager().AddObject(*winSlot4);

		GameObject* winSlot5 = GameObjectFactory::GetInstance().CreateObject("WinSlot");
		winSlot5->GetComponent<Transform>()->SetTranslation(Vector2D(264.0f, 270.0f));
		GetSpace()->GetObjectManager().AddObject(*winSlot5);

		scoreText = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		GameObject* text2 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);

		scoreText->GetComponent<SpriteText>()->SetString(""); 
		scoreText->GetComponent<SpriteText>()->SetAlignment(LEFT);
		GetSpace()->GetObjectManager().AddObject(*scoreText);
		

		text2->GetComponent<SpriteText>()->SetString("TIME");
		text2->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text2->GetComponent<Transform>()->SetTranslation(Vector2D(115.0f, -330.0f));
		GetSpace()->GetObjectManager().AddObject(*text2);
		

		currFrog = GameObjectFactory::GetInstance().CreateObject("Frog", mesh2x2, spriteSourceFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetDeathAnimations(spriteSourceDeadFrog, spriteSourceDrownFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetWinSprite(mesh1x1, spriteSourceWinFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetPurpleSprite(spriteSourceCombinedFrog);

		GameObject* wallL = GameObjectFactory::GetInstance().CreateObject("Wall", mesh1x1);
		wallL->GetComponent<Transform>()->SetTranslation(Vector2D(-336, 0));
		GetSpace()->GetObjectManager().AddObject(*wallL);
		GameObject* wallR = GameObjectFactory::GetInstance().CreateObject("Wall", mesh1x1);
		wallR->GetComponent<Transform>()->SetTranslation(Vector2D(336, 0));
		GetSpace()->GetObjectManager().AddObject(*wallR);


		timerObject = GameObjectFactory::GetInstance().CreateObject("Timer", mesh1x1);

		GetSpace()->GetObjectManager().AddObject(*timerObject);

		//GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateShip(meshShip));
		//musicChannel = soundManager->PlaySound("Asteroid Field");

		//Car type one
		GameObject* car1_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar1);
		car1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -256));
		GetSpace()->GetObjectManager().AddObject(*car1_1);

		GameObject* car1_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar1);
		car1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -256));
		GetSpace()->GetObjectManager().AddObject(*car1_2);

		GameObject* car1_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar1);
		car1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -256));
		GetSpace()->GetObjectManager().AddObject(*car1_3);

		//Car type two
		GameObject* car2_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar2);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_1->GetComponent<Transform>()->SetTranslation(Vector2D(-10, -208));
		GetSpace()->GetObjectManager().AddObject(*car2_1);

		GameObject* car2_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar2);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-190, -208));
		GetSpace()->GetObjectManager().AddObject(*car2_2);

		GameObject* car2_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar2);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-370, -208));
		GetSpace()->GetObjectManager().AddObject(*car2_3);

		//Car type three
		GameObject* car3_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar3);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -160));
		GetSpace()->GetObjectManager().AddObject(*car3_1);

		GameObject* car3_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar3);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -160));
		GetSpace()->GetObjectManager().AddObject(*car3_2);

		GameObject* car3_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar3);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -160));
		GetSpace()->GetObjectManager().AddObject(*car3_3);

		//Car type four
		GameObject* car4_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar4);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		car4_1->GetComponent<Transform>()->SetTranslation(Vector2D(-100, -112));
		GetSpace()->GetObjectManager().AddObject(*car4_1);

		//Truck
		GameObject* truck_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar5);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		truck_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_1->GetComponent<Transform>()->SetTranslation(Vector2D(50, -64));
		truck_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_1);

		GameObject* truck_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x1, spriteSourceCar5);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		truck_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		truck_2->GetComponent<Transform>()->SetTranslation(Vector2D(290, -64));
		truck_2->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		truck_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*truck_2);

		// Turtle
		GameObject* turtle_1_1 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_1->GetComponent<Behaviors::TurtleMovement>()->SetFlipAnimation(spriteSourceTurtleSink3);
		turtle_1_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 32));
		turtle_1_1->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		turtle_1_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_1);

		GameObject* turtle_1_2 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_2->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_2->GetComponent<Transform>()->SetTranslation(Vector2D(110, 32));
		turtle_1_2->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		turtle_1_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_2);

		GameObject* turtle_1_3 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_3->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_3->GetComponent<Transform>()->SetTranslation(Vector2D(-70, 32));
		turtle_1_3->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		turtle_1_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_3);

		GameObject* turtle_1_4 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_4->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_4->GetComponent<Transform>()->SetTranslation(Vector2D(-250, 32));
		turtle_1_4->GetComponent<Transform>()->SetScale(Vector2D(90, 30));
		turtle_1_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(30, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_4);

		GameObject* turtle_2_1 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_1->GetComponent<Behaviors::TurtleMovement>()->SetFlipAnimation(spriteSourceTurtleSink2);
		turtle_2_1->GetComponent<Transform>()->SetTranslation(Vector2D(360, 176));
		turtle_2_1->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		turtle_2_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(15, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_1);

		GameObject* turtle_2_2 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_2->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_2->GetComponent<Transform>()->SetTranslation(Vector2D(180, 176));
		turtle_2_2->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		turtle_2_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(15, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_2);

		GameObject* turtle_2_3 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_3->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_3->GetComponent<Transform>()->SetTranslation(Vector2D(0, 176));
		turtle_2_3->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		turtle_2_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(15, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_3);

		GameObject* turtle_2_4 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_4->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_4->GetComponent<Transform>()->SetTranslation(Vector2D(-180, 176));
		turtle_2_4->GetComponent<Transform>()->SetScale(Vector2D(60, 30));
		turtle_2_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(15, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_4);

		// Log
		GameObject* log_1_1 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogSmall);
		log_1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_1_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(45);
		log_1_1->GetComponent<Transform>()->SetTranslation(Vector2D(250, 80));
		log_1_1->GetComponent<Transform>()->SetScale(Vector2D(80, 30));
		log_1_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(25, 15));
		GetSpace()->GetObjectManager().AddObject(*log_1_1);

		GameObject* log_1_2 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogSmall);
		log_1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_1_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(45);
		log_1_2->GetComponent<Transform>()->SetTranslation(Vector2D(50, 80));
		log_1_2->GetComponent<Transform>()->SetScale(Vector2D(80, 30));
		log_1_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(25, 15));
		GetSpace()->GetObjectManager().AddObject(*log_1_2);

		GameObject* log_1_3 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogSmall);
		log_1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_1_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(45);
		log_1_3->GetComponent<Transform>()->SetTranslation(Vector2D(-150, 80));
		log_1_3->GetComponent<Transform>()->SetScale(Vector2D(80, 30));
		log_1_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(25, 15));
		GetSpace()->GetObjectManager().AddObject(*log_1_3);

		GameObject* log_2_1 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogLarge);
		log_2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 128));
		log_2_1->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		GetSpace()->GetObjectManager().AddObject(*log_2_1);

		GameObject* log_2_2 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogLarge);
		log_2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-10, 128));
		log_2_2->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		GetSpace()->GetObjectManager().AddObject(*log_2_2);

		GameObject* log_2_3 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogLarge);
		log_2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-310, 128));
		log_2_3->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		GetSpace()->GetObjectManager().AddObject(*log_2_3);

		GameObject* log_2_4 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogLarge);
		log_2_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_4->GetComponent<Transform>()->SetTranslation(Vector2D(-610, 128));
		log_2_4->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		GetSpace()->GetObjectManager().AddObject(*log_2_4);

		GameObject* log_3_1 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogMedium);
		log_3_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_3_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		log_3_1->GetComponent<Transform>()->SetTranslation(Vector2D(360, 224));
		log_3_1->GetComponent<Transform>()->SetScale(Vector2D(100, 30));
		log_3_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(35, 15));
		GetSpace()->GetObjectManager().AddObject(*log_3_1);

		GameObject* log_3_2 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogMedium);
		log_3_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_3_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		log_3_2->GetComponent<Transform>()->SetTranslation(Vector2D(180, 224));
		log_3_2->GetComponent<Transform>()->SetScale(Vector2D(100, 30));
		log_3_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(35, 15));
		GetSpace()->GetObjectManager().AddObject(*log_3_2);

		GameObject* log_3_3 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogMedium);
		log_3_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_3_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		log_3_3->GetComponent<Transform>()->SetTranslation(Vector2D(-110, 224));
		log_3_3->GetComponent<Transform>()->SetScale(Vector2D(100, 30));
		log_3_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(35, 15));
		GetSpace()->GetObjectManager().AddObject(*log_3_3);

		GameObject* log_3_4 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x1, spriteSourceLogMedium);
		log_3_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_3_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		log_3_4->GetComponent<Transform>()->SetTranslation(Vector2D(-290, 224));
		log_3_4->GetComponent<Transform>()->SetScale(Vector2D(100, 30));
		log_3_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(35, 15));
		GetSpace()->GetObjectManager().AddObject(*log_3_4);

		// PFrog
		GameObject* PFrog = GameObjectFactory::GetInstance().CreateObject("PFrog", mesh1x1, spriteSourcePFrog);
		PFrog->GetComponent<Transform>()->SetTranslation(Vector2D(235, 80));
		GetSpace()->GetObjectManager().AddObject(*PFrog);

		GetSpace()->GetObjectManager().AddObject(*currFrog);

		std::cout << "Level1::Initialize" << std::endl;
	}

	void Level1::Update(float dt)
	{

		UNREFERENCED_PARAMETER(dt);

		if (!lost)
		{

			if (currFrog->IsDestroyed() || currFrog == nullptr)
			{

				lives = Behaviors::FrogMovement::GetLives();

				if (lives < 0)
				{
					soundManager->PlaySound("LoseSong.wav");
					lost = true;
					//GetSpace()->SetLevel<Levels::Level2>();
					return;
				}

				currFrog = GameObjectFactory::GetInstance().CreateObject("Frog", mesh2x2, spriteSourceFrog);
				currFrog->GetComponent<Behaviors::FrogMovement>()->SetDeathAnimations(spriteSourceDeadFrog, spriteSourceDrownFrog);
				currFrog->GetComponent<Behaviors::FrogMovement>()->SetWinSprite(mesh1x1, spriteSourceWinFrog);

				GetSpace()->GetObjectManager().AddObject(*currFrog);

				soundManager->PlaySound("Respawn1.wav");

				timer = 40.0f;


			}
			else
			{
				scoreText->GetComponent<SpriteText>()->SetString(std::to_string(currFrog->GetComponent<Behaviors::FrogMovement>()->GetScore()));
			}

			timer = currFrog->GetComponent<Behaviors::FrogMovement>()->GetTimer();

			if (timerObject != nullptr)
			{
				//Set the scale and translation of the timer to make it display the time remaining
				Transform* timerTransform = timerObject->GetComponent<Transform>();

				timerTransform->SetTranslation(Vector2D((-timerTransform->GetScale().x / 2) + 100.0f, -330.0f));
				timerTransform->SetScale(Vector2D(timer * 5.0f, 25.0f));

				//std::cout << timerTransform->GetScale() << std::endl;
			}

			if (timer <= 0.0f)
			{
				currFrog->Destroy();
			}

			
		}

		if (lives < 2)
		{
			FrogLife2->GetComponent<Sprite>()->SetAlpha(0);
			if (lives < 1)
			{
				FrogLife1->GetComponent<Sprite>()->SetAlpha(0);
			}
		}

		

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
		delete meshText;
		delete spriteSourceText;
		delete mesh1x2;
		delete spriteSourceFrog;
		delete spriteSourceWinFrog;
		delete spriteSourceDeadFrog;
		delete mesh1x1;
		delete mesh2x2;
		delete mesh1x3;
		delete spriteSourceBackground;
		delete spriteSourceLogSmall;
		delete spriteSourceLogMedium;
		delete spriteSourceLogLarge;
		delete spriteSourceCar1;
		delete spriteSourceCar2;
		delete spriteSourceCar3;
		delete spriteSourceCar4;
		delete spriteSourceCar5;
		delete textureText;
		delete textureDeadFrog;
		delete textureFrog;
		delete textureLogLarge;
		delete textureLogMedium;
		delete textureLogSmall;
		delete textureCar1;
		delete textureCar2;
		delete textureCar3;
		delete textureCar4;
		delete textureCar5;
		delete textureWinFrog;
		delete textureBackground;
		delete textureDrownFrog;
		delete textureTurtleSink2;
		delete textureTurtleSink3;
		delete textureTurtleFloat2;
		delete textureTurtleFloat3;
		delete spriteSourceTurtleFloat2;
		delete spriteSourceTurtleFloat3;
		delete spriteSourceTurtleSink2;
		delete spriteSourceTurtleSink3;
		delete spriteSourceDrownFrog;
		delete spriteSourceCombinedFrog;
		delete textureCombinedFrog;
		soundManager->Shutdown();
		std::cout << "Level1::Unload" << std::endl;
	}
}