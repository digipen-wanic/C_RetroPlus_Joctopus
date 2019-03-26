//------------------------------------------------------------------------------
//
// File Name:	Main.cpp
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "stdafx.h"

// BetaFramework Engine
#include <Engine.h>

// Engine modules
#include "Space.h"

// Initial game state
#include "Level1.h"


#include "GameObjectFactory.h"
#include "PlayerShip.h"
#include "TimedDeath.h"
#include "MonkeyMovement.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "PlayerProjectile.h"
#include "Asteroid.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Main function
int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR command_line, _In_ int show)
{
	// Enable memory leak checking
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	// Unused parameters
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(show);
	UNREFERENCED_PARAMETER(instance);

	// Create a new space called "GameSpace"
	Space* space = new Space("GameSpace");

	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerShip>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::TimedDeath>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::MonkeyMovement>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::ColorChange>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::ScreenWrap>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::PlayerProjectile>();
	GameObjectFactory::GetInstance().RegisterComponent<Behaviors::Asteroid>();

	// Set initial level to the second level.
	space->SetLevel(new Levels::Level1());

	// Add additional modules to engine
	Engine::GetInstance().AddModule(space);
	
	// Game engine goes!
	Engine::GetInstance().Start(800, 600, 200);

	return 0;
}
