//------------------------------------------------------------------------------
//
// File Name:	Omega.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Omega.h"

#include "Level1.h"
#include "Level2.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Texture.h"
#include "MeshFactory.h"
#include "Space.h"
#include "Vector2D.h"
#include "Graphics.h"
#include "Input.h"
#include "Physics.h"
#include "Animation.h"
#include "System.h"
#include "PlayerShip.h"
#include "TimedDeath.h"
#include "GameObjectFactory.h"
#include "Archetypes.h"
#include "Asteroid.h"
#include "Level3.h"
#include "PlayerShip.h"
#include "MeshHelper.h"


namespace Levels
{
	Omega::Omega()
		: Level("Omega"), asteroidSpawnInitial(8), asteroidSpawnMaximum(20), asteroidHighScore(0)
	{

	}

	void Omega::Load()
	{
		meshShip = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));
		meshBullet = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));
		meshAsteroid = CreateQuadMesh(Vector2D(1, 1), Vector2D(0.5f, 0.5f));  

		spriteSourceShip = new SpriteSource(1, 1, Texture::CreateTextureFromFile("Ship.png"));
		spriteSourceBullet = new SpriteSource(1, 1, Texture::CreateTextureFromFile("Bullet.png"));
		spriteSourceAsteroid = new SpriteSource(1, 1, Texture::CreateTextureFromFile("Asteroid.png"));

		GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Asteroid", meshAsteroid, spriteSourceAsteroid));
		GetSpace()->GetObjectManager().AddArchetype(*GameObjectFactory::GetInstance().CreateObject("Bullet", meshBullet, spriteSourceBullet));
	}

	void Omega::Initialize()
	{
		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("PlayerShip", meshShip, spriteSourceShip));
		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Arena"));
		GetSpace()->GetObjectManager().AddObject(*GameObjectFactory::GetInstance().CreateObject("Walls", meshAsteroid));
		asteroidWaveCount = 0;
		asteroidSpawnCount = asteroidSpawnInitial;
		playerShip = GetSpace()->GetObjectManager().GetObjectByName("PlayerShip")->GetComponent<Behaviors::PlayerShip>();
		Graphics::GetInstance().SetBackgroundColor(Colors::Black);
	}

	void Omega::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		if (GetSpace()->GetObjectManager().GetObjectCount("Asteroid") == 0)
		{
			SpawnAsteroidWave();
		}

		UpdateScore();
		SwitchLevels();



	}

	void Omega::Shutdown()
	{
		if (playerShip->GetScore() > asteroidHighScore)
		{
			asteroidHighScore = playerShip->GetScore();
		}
	}

	void Omega::Unload()
	{
		delete meshShip;
		delete meshBullet;
		delete meshAsteroid;

		delete spriteSourceShip;
		delete spriteSourceBullet;
		delete spriteSourceAsteroid;
	}

	void Omega::SpawnAsteroid()
	{
		GameObject* newAsteroid = new GameObject(*GetSpace()->GetObjectManager().GetArchetypeByName("Asteroid"));
		GetSpace()->GetObjectManager().AddObject(*newAsteroid);
	}

	void Omega::SpawnAsteroidWave()
	{
		asteroidWaveCount++;

		for (unsigned i = 0; i < asteroidSpawnCount; i++)
		{
			SpawnAsteroid();
		}

		asteroidSpawnCount++;

		if (asteroidSpawnCount > asteroidSpawnMaximum)
		{
			asteroidSpawnCount = asteroidSpawnMaximum;
		}
	}

	void Omega::UpdateScore()
	{
		sprintf_s(windowTitle, titleStringLength, "Asteroids: Wave = %d, Score = %d, High Score = %d", asteroidWaveCount, playerShip->GetScore(), asteroidHighScore);
		System::GetInstance().SetWindowTitle(windowTitle);
	}

	void Omega::SwitchLevels()
	{
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
}