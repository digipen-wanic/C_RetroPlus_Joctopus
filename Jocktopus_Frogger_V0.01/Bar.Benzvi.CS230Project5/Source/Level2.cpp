//------------------------------------------------------------------------------
//
// File Name:	Level2.cpp
// Author(s):	Bar Ben-zvi, Freddy Martin
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
#include "SoundManager.h"
#include <fmod.hpp>
#include "Parser.h"
#include "GameObjectFactory.h"
#include "Texture.h"
#include "SpriteSource.h"
#include "SpriteText.h"
#include "ItemMovement.h"
#include "ColliderRectangle.h"
#include "FrogMovement.h"
#include "TurtleMovement.h"
#include <Graphics.h>
#include "WinSlot.h"
#include "MainMenu.h"
#include "Random.h"
#include <Animation.h>

namespace Levels
{
	Level2::Level2()
		: Level("Level2"), mesh1x1(nullptr), mesh1x2(nullptr), lives(2), timer(1.0f), winLoseTimer(5.0f), flyAliveTimer(2.5f),
		flySpawnTimer(3.0f), winLoseSequenceInit(false), lost(false), won(false)
	{

	}

	void Level2::Load()
	{

		soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundManager->AddEffect("Robbit.wav");
		soundManager->AddEffect("DieBubbles.wav");
		soundManager->AddMusic("PlusSong.wav");
		soundManager->AddEffect("PlusRespawn1.wav");
		soundManager->AddEffect("PlusLoseSong.wav");
		soundManager->AddEffect("PlusWinSong.wav");
		soundManager->AddEffect("PlusJump.wav");
		soundManager->AddEffect("PlusDieExplosion.wav");
		soundManager->AddEffect("DieBubbles.wav");


		mesh1x1 = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		mesh1x2 = CreateQuadMesh(Vector2D(1.0f, 1.0f / 2.0f), Vector2D(0.5f, 0.5f));
		mesh2x2 = CreateQuadMesh(Vector2D(1.0f / 2.0f, 1.0f / 2.0f), Vector2D(0.5f, 0.5f));
		mesh1x3 = CreateQuadMesh(Vector2D(1.0f, 1.0f / 3.0f), Vector2D(0.5f, 0.5f));
		mesh3x3 = CreateQuadMesh(Vector2D(1.0f / 3.0f, 1.0f / 3.0f), Vector2D(0.5f, 0.5f));

		meshText = CreateQuadMesh(Vector2D(1.0f / 6.0f, 1.0f / 6.0f), Vector2D(0.5f, 0.5f));
		textureText = Texture::CreateTextureFromFile("NumberLetterSpriteSheet.png");
		spriteSourceText = new SpriteSource(6, 6, textureText);

		textureBackground = Texture::CreateTextureFromFile("PlusBackground.jpg");
		spriteSourceBackground = new SpriteSource(1, 1, textureBackground);

		textureDeadFrog = Texture::CreateTextureFromFile("Explode.png");
		spriteSourceDeadFrog = new SpriteSource(2, 2, textureDeadFrog);

		textureDrownFrog = Texture::CreateTextureFromFile("RoboFrogDrown.png");
		spriteSourceDrownFrog = new SpriteSource(2, 2, textureDrownFrog);

		textureFrog = Texture::CreateTextureFromFile("RoboFrogJump.png");
		spriteSourceFrog = new SpriteSource(2, 2, textureFrog);

		textureWinFrog = Texture::CreateTextureFromFile("Helicopter.png");
		spriteSourceWinFrog = new SpriteSource(1, 1, textureWinFrog);

		textureWinFrog2 = Texture::CreateTextureFromFile("Helicopter.png");
		spriteSourceWinFrog2 = new SpriteSource(1, 1, textureWinFrog2);

		textureLogLarge = Texture::CreateTextureFromFile("FloatingBarrels.png");
		spriteSourceLogLarge = new SpriteSource(1, 2, textureLogLarge);

		textureLogMedium = Texture::CreateTextureFromFile("WoodenPlanks (done).png");
		spriteSourceLogMedium = new SpriteSource(1, 1, textureLogMedium);

		textureLogSmall = Texture::CreateTextureFromFile("car.png");
		spriteSourceLogSmall = new SpriteSource(1, 1, textureLogSmall);

		textureCar3 = Texture::CreateTextureFromFile("Tank(PinkCar)(done).png");
		spriteSourceCar3 = new SpriteSource(1, 2, textureCar3);

		textureCar4 = Texture::CreateTextureFromFile("ToxicBarrel.png");
		spriteSourceCar4 = new SpriteSource(3, 3, textureCar4);

		textureCar5 = Texture::CreateTextureFromFile("plusTruck.png");
		spriteSourceCar5 = new SpriteSource(1, 1, textureCar5);

		textureTurtleFloat2 = Texture::CreateTextureFromFile("RoboSwimDouble.png");
		spriteSourceTurtleFloat2 = new SpriteSource(1, 3, textureTurtleFloat2);

		textureTurtleFloat3 = Texture::CreateTextureFromFile("RoboSwimTriple.png");
		spriteSourceTurtleFloat3 = new SpriteSource(1, 3, textureTurtleFloat3);

		textureTurtleSink2 = Texture::CreateTextureFromFile("RoboRollDouble.png");
		spriteSourceTurtleSink2 = new SpriteSource(1, 3, textureTurtleSink2);

		textureTurtleSink3 = Texture::CreateTextureFromFile("RoboRollTriple.png");
		spriteSourceTurtleSink3 = new SpriteSource(1, 3, textureTurtleSink3);

		textureSnake = Texture::CreateTextureFromFile("Tornado2.png");
		spriteSourceSnake = new SpriteSource(2, 2, textureSnake);

		std::cout << "Level2::Load" << std::endl;
	}

	void Level2::Initialize()
	{

		soundManager->PlaySound("PlusSong.wav");
		soundManager->SetMusicVolume(0.7f);
		soundManager->SetEffectsVolume(0.5f);

		GameObject* background = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh1x1, spriteSourceBackground);
		background->GetComponent<Transform>()->SetScale(Vector2D(672, 768));
		GetSpace()->GetObjectManager().AddObject(*background);

		FrogLife1 = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh2x2, spriteSourceFrog);
		FrogLife1->GetComponent<Transform>()->SetScale(Vector2D(35, 35));
		FrogLife1->GetComponent<Sprite>()->SetAlpha(1.0f);
		FrogLife1->GetComponent<Transform>()->SetTranslation(Vector2D(Graphics::GetInstance().GetScreenWorldDimensions().left + 25, -335));
		GetSpace()->GetObjectManager().AddObject(*FrogLife1);

		FrogLife2 = GameObjectFactory::GetInstance().CreateObject("BasicSprite", mesh2x2, spriteSourceFrog);
		FrogLife2->GetComponent<Transform>()->SetScale(Vector2D(35, 35));
		FrogLife2->GetComponent<Sprite>()->SetAlpha(1.0f);
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

		winSlots.push_back(winSlot1);
		winSlots.push_back(winSlot2);
		winSlots.push_back(winSlot3);
		winSlots.push_back(winSlot4);
		winSlots.push_back(winSlot5);



		scoreText = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		scoreText->GetComponent<SpriteText>()->SetString("");
		scoreText->GetComponent<SpriteText>()->SetAlignment(LEFT);
		scoreText->GetComponent<Transform>()->SetScale(Vector2D(16.0f, 18.0f));
		GetSpace()->GetObjectManager().AddObject(*scoreText);

		highScoreText = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		highScoreText->GetComponent<SpriteText>()->SetString("");
		highScoreText->GetComponent<SpriteText>()->SetAlignment(LEFT);
		highScoreText->GetComponent<Transform>()->SetScale(Vector2D(16.0f, 18.0f));
		highScoreText->GetComponent<Transform>()->SetTranslation(Vector2D(-64.0f, 344.0f));
		GetSpace()->GetObjectManager().AddObject(*highScoreText);

		GameObject* text1 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text1->GetComponent<SpriteText>()->SetString("TIME");
		text1->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text1->GetComponent<Transform>()->SetTranslation(Vector2D(115.0f, -357.0f));
		GetSpace()->GetObjectManager().AddObject(*text1);

		GameObject* text2 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text2->GetComponent<SpriteText>()->SetString("SCORE");
		text2->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text2->GetComponent<Transform>()->SetTranslation(Vector2D(-320.0f, 368.0f));
		GetSpace()->GetObjectManager().AddObject(*text2);

		GameObject* text3 = GameObjectFactory::GetInstance().CreateObject("SpriteText", meshText, spriteSourceText);
		text3->GetComponent<SpriteText>()->SetString("HIGH SCORE");
		text3->GetComponent<SpriteText>()->SetAlignment(LEFT);
		text3->GetComponent<Transform>()->SetTranslation(Vector2D(-64.0f, 368.0f));
		GetSpace()->GetObjectManager().AddObject(*text3);


		currFrog = GameObjectFactory::GetInstance().CreateObject("Frog", mesh2x2, spriteSourceFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetDeathAnimations(spriteSourceDeadFrog, spriteSourceDrownFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetWinSprite(mesh1x1, spriteSourceWinFrog);
		currFrog->GetComponent<Behaviors::FrogMovement>()->SetSounds("Robbit.wav", "PlusJump.wav", "PlusDieExplosion.wav");

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
		GameObject* car1_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -256));
		car1_1->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car1_1);

		GameObject* car1_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -256));
		car1_2->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car1_2);

		GameObject* car1_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car1_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -256));
		car1_3->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car1_3);

		//Car type two
		GameObject* car2_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_1->GetComponent<Transform>()->SetTranslation(Vector2D(-10, -208));
		car2_1->GetComponent<Transform>()->SetScale(Vector2D(-car2_1->GetComponent<Transform>()->GetScale().x, car2_1->GetComponent<Transform>()->GetScale().y));
		car2_1->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car2_1);

		GameObject* car2_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-190, -208));
		car2_2->GetComponent<Transform>()->SetScale(Vector2D(-car2_2->GetComponent<Transform>()->GetScale().x, car2_2->GetComponent<Transform>()->GetScale().y));
		car2_2->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car2_2);

		GameObject* car2_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(35);
		car2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-370, -208));
		car2_3->GetComponent<Transform>()->SetScale(Vector2D(-car2_3->GetComponent<Transform>()->GetScale().x, car2_3->GetComponent<Transform>()->GetScale().y));
		car2_3->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car2_3);

		//Car type three
		GameObject* car3_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x2, spriteSourceCar3);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_1->GetComponent<Transform>()->SetTranslation(Vector2D(10, -160));
		car3_1->GetComponent<Animation>()->Play(0, 2, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car3_1);

		GameObject* car3_2 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x2, spriteSourceCar3);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_2->GetComponent<Transform>()->SetTranslation(Vector2D(190, -160));
		car3_2->GetComponent<Animation>()->Play(0, 2, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car3_2);

		GameObject* car3_3 = GameObjectFactory::GetInstance().CreateObject("Car", mesh1x2, spriteSourceCar3);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		car3_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(40);
		car3_3->GetComponent<Transform>()->SetTranslation(Vector2D(370, -160));
		car3_3->GetComponent<Animation>()->Play(0, 2, 0.1f, true);
		GetSpace()->GetObjectManager().AddObject(*car3_3);

		//Car type four
		GameObject* car4_1 = GameObjectFactory::GetInstance().CreateObject("Car", mesh3x3, spriteSourceCar4);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		car4_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(60);
		car4_1->GetComponent<Transform>()->SetTranslation(Vector2D(-100, -112));
		car4_1->GetComponent<Transform>()->SetScale(Vector2D(-car4_1->GetComponent<Transform>()->GetScale().x, car4_1->GetComponent<Transform>()->GetScale().y));
		car4_1->GetComponent<Animation>()->Play(0, 8, 0.1f, true);
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

		//Snake. Snake! SNAKE!!!
		GameObject* snake = GameObjectFactory::GetInstance().CreateObject("Snake", mesh2x2, spriteSourceSnake);
		snake->GetComponent<Transform>()->SetTranslation(Vector2D(0, -16));
		snake->GetComponent<Animation>()->Play(0, 4, 0.5f, true);
		GetSpace()->GetObjectManager().AddObject(*snake);

		// Turtle
		GameObject* turtle_1_1 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_1->GetComponent<Behaviors::TurtleMovement>()->SetFlipAnimation(spriteSourceTurtleSink3);
		turtle_1_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 32));
		turtle_1_1->GetComponent<Transform>()->SetScale(Vector2D(120, 45));
		turtle_1_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_1);

		GameObject* turtle_1_2 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_2->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_2->GetComponent<Transform>()->SetTranslation(Vector2D(110, 32));
		turtle_1_2->GetComponent<Transform>()->SetScale(Vector2D(120, 45));
		turtle_1_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_2);

		GameObject* turtle_1_3 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_3->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_3->GetComponent<Transform>()->SetTranslation(Vector2D(-70, 32));
		turtle_1_3->GetComponent<Transform>()->SetScale(Vector2D(120, 45));
		turtle_1_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_3);

		GameObject* turtle_1_4 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat3);
		turtle_1_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_1_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(55);
		turtle_1_4->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_1_4->GetComponent<Transform>()->SetTranslation(Vector2D(-250, 32));
		turtle_1_4->GetComponent<Transform>()->SetScale(Vector2D(120, 45));
		turtle_1_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(45, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_1_4);

		GameObject* turtle_2_1 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_1->GetComponent<Behaviors::TurtleMovement>()->SetFlipAnimation(spriteSourceTurtleSink2);
		turtle_2_1->GetComponent<Transform>()->SetTranslation(Vector2D(360, 176));
		turtle_2_1->GetComponent<Transform>()->SetScale(Vector2D(90, 45));
		turtle_2_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(22.5f, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_1);

		GameObject* turtle_2_2 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_2->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_2->GetComponent<Transform>()->SetTranslation(Vector2D(180, 176));
		turtle_2_2->GetComponent<Transform>()->SetScale(Vector2D(90, 45));
		turtle_2_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(22.5f, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_2);

		GameObject* turtle_2_3 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_3->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_3->GetComponent<Transform>()->SetTranslation(Vector2D(0, 176));
		turtle_2_3->GetComponent<Transform>()->SetScale(Vector2D(90, 45));
		turtle_2_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(22.5f, 15));
		GetSpace()->GetObjectManager().AddObject(*turtle_2_3);

		GameObject* turtle_2_4 = GameObjectFactory::GetInstance().CreateObject("Turtle", mesh1x3, spriteSourceTurtleFloat2);
		turtle_2_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(-1);
		turtle_2_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(65);
		turtle_2_4->GetComponent<Behaviors::TurtleMovement>()->SetActive(false);
		turtle_2_4->GetComponent<Transform>()->SetTranslation(Vector2D(-180, 176));
		turtle_2_4->GetComponent<Transform>()->SetScale(Vector2D(90, 45));
		turtle_2_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(22.5f, 15));
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

		GameObject* log_2_1 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x2, spriteSourceLogLarge);
		log_2_1->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_1->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_1->GetComponent<Transform>()->SetTranslation(Vector2D(290, 128));
		log_2_1->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_1->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		log_2_1->GetComponent<Animation>()->Play(0, 2, 1, true);
		GetSpace()->GetObjectManager().AddObject(*log_2_1);

		GameObject* log_2_2 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x2, spriteSourceLogLarge);
		log_2_2->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_2->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_2->GetComponent<Transform>()->SetTranslation(Vector2D(-10, 128));
		log_2_2->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_2->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		log_2_2->GetComponent<Animation>()->Play(0, 2, 1, true);
		GetSpace()->GetObjectManager().AddObject(*log_2_2);

		GameObject* log_2_3 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x2, spriteSourceLogLarge);
		log_2_3->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_3->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_3->GetComponent<Transform>()->SetTranslation(Vector2D(-310, 128));
		log_2_3->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_3->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		log_2_3->GetComponent<Animation>()->Play(0, 2, 1, true);
		GetSpace()->GetObjectManager().AddObject(*log_2_3);

		GameObject* log_2_4 = GameObjectFactory::GetInstance().CreateObject("Log", mesh1x2, spriteSourceLogLarge);
		log_2_4->GetComponent<Behaviors::ItemMovement>()->SetDirection(1);
		log_2_4->GetComponent<Behaviors::ItemMovement>()->SetSpeed(75);
		log_2_4->GetComponent<Transform>()->SetTranslation(Vector2D(-610, 128));
		log_2_4->GetComponent<Transform>()->SetScale(Vector2D(180, 30));
		log_2_4->GetComponent<ColliderRectangle>()->SetExtents(Vector2D(75, 15));
		log_2_4->GetComponent<Animation>()->Play(0, 2, 1, true);
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

		GetSpace()->GetObjectManager().AddObject(*currFrog);

		std::cout << "Level2::Initialize" << std::endl;
	}

	void Level2::Update(float dt)
	{
		if (won)
		{
			if (!winLoseSequenceInit)
			{
				soundManager->SetMusicVolume(0.0f);
				soundManager->PlaySound("PlusWinSong.wav");
				winLoseSequenceInit = true;
				winLoseTimer = 3.0f;

				for (auto it = winSlots.cbegin(); it != winSlots.cend(); ++it)
				{
					GameObject* winFrog = GameObjectFactory::GetInstance().CreateObject("WinFrog", mesh1x1, spriteSourceWinFrog2);
					winFrog->GetComponent<Transform>()->SetTranslation((*it)->GetComponent<Transform>()->GetTranslation());
					GetSpace()->GetObjectManager().AddObject(*winFrog);
				}
			}

			winLoseTimer -= dt;
			if (winLoseTimer <= 0.0f)
			{
				GetSpace()->SetLevel<MainMenu>();
			}
		}
		else if (!lost)
		{

			int slotsFull = 0;

			for (auto it = winSlots.cbegin(); it != winSlots.cend(); ++it)
			{
				if ((*it)->GetComponent<Behaviors::WinSlot>()->GetContainsFrog())
				{
					slotsFull++;
				}
			}

			if (slotsFull == 5)
			{
				won = true;
			}

			if (currFrog->IsDestroyed() || currFrog == nullptr)
			{
				timer -= dt;

				if (timer <= 0.0f)
				{
					lives = Behaviors::FrogMovement::GetLives();

					if (lives < 0)
					{
						soundManager->SetMusicVolume(0.0f);
						lost = true;
						//GetSpace()->SetLevel<Levels::Level2>();
						return;
					}

					currFrog = GameObjectFactory::GetInstance().CreateObject("Frog", mesh2x2, spriteSourceFrog);
					currFrog->GetComponent<Behaviors::FrogMovement>()->SetDeathAnimations(spriteSourceDeadFrog, spriteSourceDrownFrog);
					currFrog->GetComponent<Behaviors::FrogMovement>()->SetWinSprite(mesh1x1, spriteSourceWinFrog);
					currFrog->GetComponent<Behaviors::FrogMovement>()->SetSounds("Robbit.wav", "PlusJump.wav", "PlusDieExplosion.wav");

					GetSpace()->GetObjectManager().AddObject(*currFrog);

					soundManager->PlaySound("Respawn1.wav");

					timer = 1.0f;
				}
				return;


			}
			else
			{
				scoreText->GetComponent<SpriteText>()->SetString(std::to_string(Behaviors::FrogMovement::GetScore()));
				highScoreText->GetComponent<SpriteText>()->SetString(std::to_string(Behaviors::FrogMovement::GetHighScore()));
			}

			if (currFrog->GetComponent<Behaviors::FrogMovement>() != nullptr)
			{

				if (timerObject != nullptr && !currFrog->IsDestroyed())
				{
					//Set the scale and translation of the timer to make it display the time remaining
					Transform* timerTransform = timerObject->GetComponent<Transform>();

					timerTransform->SetTranslation(Vector2D((-timerTransform->GetScale().x / 2) + 100.0f, -357.0f));
					timerTransform->SetScale(Vector2D(currFrog->GetComponent<Behaviors::FrogMovement>()->GetTimer() * 5.0f, 25.0f));

					//std::cout << timerTransform->GetScale() << std::endl;
				}

				if (currFrog->GetComponent<Behaviors::FrogMovement>()->GetTimer() <= 0.0f)
				{
					currFrog->Destroy();
				}
			}


		}
		else
		{
			if (!winLoseSequenceInit)
			{
				soundManager->PlaySound("PlusLoseSong.wav");
				winLoseSequenceInit = true;
				winLoseTimer = 5.0f;
			}

			winLoseTimer -= dt;

			if (winLoseTimer <= 0)
			{
				GetSpace()->SetLevel<MainMenu>();
				Behaviors::FrogMovement::ResetScore();
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


	}

	void Level2::Shutdown()
	{
		currFrog = nullptr;
		winSlots.clear();
		timerObject = nullptr;
		scoreText = nullptr;
		highScoreText = nullptr;
		Behaviors::FrogMovement::SetLives(2);
		lives = Behaviors::FrogMovement::GetLives();
		FrogLife1 = nullptr;
		FrogLife2 = nullptr;
	}

	void Level2::Unload()
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
		delete mesh3x3;
		delete spriteSourceBackground;
		delete spriteSourceLogSmall;
		delete spriteSourceLogMedium;
		delete spriteSourceLogLarge;
		delete spriteSourceCar3;
		delete spriteSourceCar4;
		delete spriteSourceCar5;
		delete textureText;
		delete textureDeadFrog;
		delete textureFrog;
		delete textureLogLarge;
		delete textureLogMedium;
		delete textureLogSmall;
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
		delete spriteSourceWinFrog2;
		delete textureWinFrog2;
		delete textureSnake;
		delete spriteSourceSnake;

		soundManager->Shutdown();
		std::cout << "Level2::Unload" << std::endl;
	}
}