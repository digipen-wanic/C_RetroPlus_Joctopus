//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameObjectFactory.h"
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "SpriteTilemap.h"
#include "Animation.h"
#include "Parser.h"
#include "ColliderLine.h"
#include "SpriteText.h"


GameObject* GameObjectFactory::CreateObject(const std::string& name, Mesh* mesh, SpriteSource* spriteSource)
{
	GameObject* object = new GameObject(name);

	Parser parser(objectFilePath + name + ".txt", std::fstream::in);

	try
	{
		std::cout << "hmm" << std::endl;
		object->Deserialize(parser);
		if (object->GetComponent("Sprite") != nullptr)
		{
			static_cast<Sprite*>(object->GetComponent("Sprite"))->SetMesh(mesh);
			static_cast<Sprite*>(object->GetComponent("Sprite"))->SetSpriteSource(spriteSource);
		}
		return object;
	}
	catch (ParseException& exception)
	{
		std::cout << exception.what();

		delete object;
		object = nullptr;

		return object;
	}

	
}
Component* GameObjectFactory::CreateComponent(const std::string& name)
{
	for (auto it = registeredComponents.cbegin(); it < registeredComponents.cend(); ++it)
	{
		std::string string(typeid(**it).name());
		string = string.substr(6);

		if (string == name)
		{
			return (*it)->Clone();
		}
	}

	return nullptr;
}

void GameObjectFactory::SaveObjectToFile(GameObject* object)
{
	Parser parser(objectFilePath + object->GetName() + ".txt", std::fstream::out);

	object->Serialize(parser);

	std::cout << object->GetName() << " was serialized" << std::endl;
}

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory factory;
	
	return factory;
}


GameObjectFactory::GameObjectFactory()
	: objectFilePath("Assets/Objects/")
{
	RegisterComponent<Sprite>();
	RegisterComponent<Physics>();
	RegisterComponent<Transform>();
	RegisterComponent<ColliderRectangle>();
	RegisterComponent<ColliderTilemap>();
	RegisterComponent<ColliderCircle>();
	RegisterComponent<ColliderPoint>();
	RegisterComponent<SpriteTilemap>();
	RegisterComponent<Animation>();
	RegisterComponent<ColliderLine>();
	RegisterComponent<SpriteText>();

}

GameObjectFactory::~GameObjectFactory()
{
	for (auto it = registeredComponents.cbegin(); it < registeredComponents.cend(); ++it)
	{
		delete *it;
	}
	registeredComponents.clear();
}

#include "Sprite.h"
#include "Physics.h"
#include "Transform.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "SpriteTilemap.h"
#include "Animation.h"