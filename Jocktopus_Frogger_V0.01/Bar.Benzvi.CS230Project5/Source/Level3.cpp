//------------------------------------------------------------------------------
//
// File Name:	Level3.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Level3.h"
#include "MeshHelper.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Space.h"
#include "Transform.h"
#include "Physics.h"
#include "Level2.h"
#include "Input.h"
#include "Level1.h"
#include "Mesh.h"
#include "GameObjectFactory.h"
#include "Omega.h"

namespace Levels
{
	Level3::Level3()
		: Level("Level3"), circleSpeed(100.0f), pointSpeed(100.0f)
	{
	}

	void Level3::Load()
	{
		meshQuad = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		textureCircle = Texture::CreateTextureFromFile("Circle.png");
		spriteSourceCircle = new SpriteSource(1, 1, textureCircle);
	}

	void Level3::Initialize()
	{
		//Create a bunch of objects
		GameObject* circle1 = GameObjectFactory::GetInstance().CreateObject("Circle", meshQuad, spriteSourceCircle);
		GameObject* circle2 = GameObjectFactory::GetInstance().CreateObject("Circle", meshQuad, spriteSourceCircle);
		GameObject* point1 = GameObjectFactory::GetInstance().CreateObject("Point", meshQuad, spriteSourceCircle);
		GameObject* rect1 = GameObjectFactory::GetInstance().CreateObject("Rectangle", meshQuad);
		GameObject* rect2 = GameObjectFactory::GetInstance().CreateObject("Rectangle", meshQuad);


		static_cast<Transform*>(point1->GetComponent("Transform"))->SetTranslation(Vector2D(0.0f, 200.0f));
		static_cast<Transform*>(rect1->GetComponent("Transform"))->SetTranslation(Vector2D(-300.0f, 300.0f));
		static_cast<Transform*>(rect2->GetComponent("Transform"))->SetTranslation(Vector2D(200.0f, -200.0f));
		static_cast<Transform*>(circle2->GetComponent("Transform"))->SetTranslation(Vector2D(300.0f, 0.0f));

		static_cast<Physics*>(point1->GetComponent("Physics"))->SetVelocity(Vector2D(0.0f, -pointSpeed));
		static_cast<Physics*>(rect1->GetComponent("Physics"))->SetVelocity(Vector2D(pointSpeed, -pointSpeed));
		static_cast<Physics*>(circle2->GetComponent("Physics"))->SetVelocity(Vector2D(-circleSpeed, 0.0f));

		GetSpace()->GetObjectManager().AddObject(*circle1);
		GetSpace()->GetObjectManager().AddObject(*point1);
		GetSpace()->GetObjectManager().AddObject(*rect1);
		GetSpace()->GetObjectManager().AddObject(*rect2);
		GetSpace()->GetObjectManager().AddObject(*circle2);
	}

	void Level3::Update(float dt)
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

	void Level3::Unload()
	{
		delete meshQuad;
		delete textureCircle;
		delete spriteSourceCircle;
	}
}