//------------------------------------------------------------------------------
//
// File Name:	GameObjectManager.cpp
// Author(s):	Bar Ben-zvi
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "Space.h"
#include "Collider.h"


GameObjectManager::GameObjectManager(Space* space)
	: BetaObject("ObjectManager", space), fixedUpdateDt(1.0f / 60.0f), timeAccumulator(0.0f)
{
}

GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

void GameObjectManager::Update(float dt)
{
	if (!static_cast<Space*>(GetParent())->IsPaused())
	{
		VariableUpdate(dt);
		FixedUpdate(dt);
	}

	DestroyObjects();
	Draw();
}

void GameObjectManager::Shutdown()
{
	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
	{
		delete *it;
	}

	gameObjectActiveList.clear();
}

void GameObjectManager::Unload()
{
	for (auto it = gameObjectArchetypes.cbegin(); it != gameObjectArchetypes.cend(); ++it)
	{
		delete *it;
	}

	gameObjectArchetypes.clear();
}

void GameObjectManager::AddObject(GameObject& gameObject)
{
	gameObject.SetParent(GetParent());
	gameObject.Initialize();
	gameObjectActiveList.push_back(&gameObject);
}

void GameObjectManager::AddArchetype(GameObject& gameObject)
{
	gameObjectArchetypes.push_back(&gameObject);
}

GameObject* GameObjectManager::GetObjectByName(const std::string& objectName) const
{
	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
	{
		if ((*it)->GetName() == objectName)
		{
			return (*it);
		}
	}

	return nullptr;
}

GameObject* GameObjectManager::GetArchetypeByName(const std::string& objectName) const
{
	for (auto it = gameObjectArchetypes.cbegin(); it != gameObjectArchetypes.cend(); ++it)
	{
		if ((*it)->GetName() == objectName)
		{
			return (*it);
		}
	}

	return nullptr;
}

unsigned GameObjectManager::GetObjectCount(const std::string& objectName) const
{
	unsigned count = 0;

	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
	{
		if ((*it)->GetName() == objectName && !((*it)->IsDestroyed()))
		{
			count++;
		}
	}

	return count;
}

void GameObjectManager::VariableUpdate(float dt)
{
	for (int i = 0; i < gameObjectActiveList.size(); i++)
	{
		gameObjectActiveList[i]->Update(dt);
	}
}

void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;

	while (timeAccumulator >= fixedUpdateDt)
	{

		for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
		{
			(*it)->FixedUpdate(fixedUpdateDt);
		}

		CheckCollisions();

		timeAccumulator -= fixedUpdateDt;

	}
}

void GameObjectManager::DestroyObjects()
{
	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend();)
	{
		if ((*it)->IsDestroyed())
		{
			delete *it;

			it = gameObjectActiveList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameObjectManager::Draw()
{
	for (auto it = gameObjectActiveList.cbegin(); it != gameObjectActiveList.cend(); ++it)
	{
		(*it)->Draw();
	}
}


void GameObjectManager::CheckCollisions()
{
	for (unsigned i = 0; i < gameObjectActiveList.size(); ++i)
	{
		if (!(gameObjectActiveList[i])->IsDestroyed())
		{
			Collider* obj1Collider = gameObjectActiveList[i]->GetComponent<Collider>();
			if (obj1Collider != nullptr)
			{
				for (unsigned j = i + 1; j < gameObjectActiveList.size(); ++j)
				{
					if (!(gameObjectActiveList[j])->IsDestroyed())
					{
						Collider* obj2Collider = gameObjectActiveList[j]->GetComponent<Collider>();

						if (obj2Collider != nullptr)
						{
							obj1Collider->CheckCollision(*obj2Collider);
						}

					}
				}
			}
		}
	}
}
