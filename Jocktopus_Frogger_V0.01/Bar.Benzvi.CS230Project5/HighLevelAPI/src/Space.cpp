//------------------------------------------------------------------------------
//
// File Name:	Space.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "Space.h"
#include "Level.h"



Space::Space(const std::string& name)
	: BetaObject(name), paused(false), currentLevel(nullptr), nextLevel(nullptr), objectManager(this)
{

}

Space::~Space()
{
	Shutdown();
}

void Space::Update(float dt)
{

	if (nextLevel != nullptr)
	{
		ChangeLevel();
	}

	if (currentLevel != nullptr && !paused)
	{
		currentLevel->Update(dt);
		objectManager.Update(dt);
	}
}

void Space::Shutdown()
{
	

	if (currentLevel != nullptr)
	{
		currentLevel->Shutdown();
		currentLevel->Unload();
		delete currentLevel;
		currentLevel = nullptr;
		objectManager.Shutdown();
		objectManager.Unload();
	}

	
}

bool Space::IsPaused() const
{
	return paused;
}


const std::string& Space::GetLevelName() const
{
	return currentLevel->GetName();
}

void Space::SetPaused(bool value)
{
	paused = value;
}

void Space::SetLevel(Level* level)
{
	nextLevel = level;
	nextLevel->SetParent(this);
}


void Space::RestartLevel()
{

	nextLevel = currentLevel;
}

void Space::ChangeLevel()
{

	//If we are switching to a new level
	if (nextLevel != currentLevel)
	{
		//If we are switching from a level, we need to unload and delete it
		if (currentLevel != nullptr)
		{
			currentLevel->Shutdown();
			objectManager.Shutdown();
			currentLevel->Unload();
			objectManager.Unload();
			delete currentLevel;
		}
		currentLevel = nextLevel;
		nextLevel = nullptr;
		currentLevel->Load();
		currentLevel->Initialize();
	}
	//Otherwise we are restarting the current level
	else if (currentLevel != nullptr && nextLevel == currentLevel)
	{
		currentLevel->Shutdown();
		objectManager.Shutdown();
		currentLevel->Initialize();
		nextLevel = nullptr;
	}
}

GameObjectManager& Space::GetObjectManager()
{
	return objectManager;
}
