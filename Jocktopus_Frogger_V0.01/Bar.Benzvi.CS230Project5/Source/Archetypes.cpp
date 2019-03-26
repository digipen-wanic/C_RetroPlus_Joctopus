//------------------------------------------------------------------------------
//
// File Name:	Archetypes.cpp
// Author(s):	Bar Ben-zvi
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Archetypes.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Physics.h"
#include "Component.h"
#include "Animation.h"
#include "TimedDeath.h"
#include "PlayerShip.h"
#include "MonkeyMovement.h"
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "ColorChange.h"
#include "ScreenWrap.h"
#include "Tilemap.h"
#include "SpriteTilemap.h"
#include "ColliderTilemap.h"
#include "GameObjectFactory.h"


namespace Archetypes
{
	GameObject* CreateShip(Mesh* mesh)
	{
		GameObject* ship = new GameObject("Ship");

		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(50.0f, 50.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);

		Physics* physics = new Physics();

		Behaviors::PlayerShip* playerShip = new Behaviors::PlayerShip(100.0f, 200.0f, static_cast<float>(M_PI), 250.0f);

		
		ship->AddComponent(transform);
		ship->AddComponent(sprite);
		ship->AddComponent(physics);
		ship->AddComponent(playerShip);

		GameObjectFactory::GetInstance().SaveObjectToFile(ship);

		return ship;
	}

	GameObject* CreateBulletArchetype(Mesh* mesh)
	{
		GameObject* bullet = new GameObject("Bullet");

		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(7.0f, 7.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);

		Physics* physics = new Physics();

		Behaviors::TimedDeath* timedDeath = new Behaviors::TimedDeath(3.0f);

		
		bullet->AddComponent(transform);
		bullet->AddComponent(sprite);
		bullet->AddComponent(physics);
		bullet->AddComponent(timedDeath);

		GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

		return bullet;

	}

	GameObject* CreateMonkey(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* monkey = new GameObject("Monkey");

		Transform* transform = new Transform(-200.0f, -400.0f);
		transform->SetScale(Vector2D(100.0f, 100.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		Animation* animation = new Animation();

		Physics* physics = new Physics();

		Behaviors::MonkeyMovement* movement = new Behaviors::MonkeyMovement();

		ColliderRectangle* collider = new ColliderRectangle(transform->GetScale() / 2.0f);

		monkey->AddComponent(transform);
		monkey->AddComponent(sprite);
		monkey->AddComponent(physics);
		monkey->AddComponent(animation);
		monkey->AddComponent(movement);
		monkey->AddComponent(collider);

		GameObjectFactory::GetInstance().SaveObjectToFile(monkey);

		return monkey;
	}

	GameObject* CreatePoint(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* point = new GameObject("Point");

		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(20.0f, 20.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		Physics* physics = new Physics();

		ColliderPoint* collider = new ColliderPoint();

		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Blue, Colors::Red);

		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

		point->AddComponent(transform);
		point->AddComponent(sprite);
		point->AddComponent(physics);
		point->AddComponent(collider);
		point->AddComponent(colorChange);
		point->AddComponent(screenWrap);

		GameObjectFactory::GetInstance().SaveObjectToFile(point);

		return point;

	}

	GameObject* CreateCircle(Mesh* mesh, SpriteSource* spriteSource)
	{
		GameObject* circle = new GameObject("Circle");

		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(100.0f, 100.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		Physics* physics = new Physics();

		ColliderCircle* collider = new ColliderCircle(50.0f);

		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Yellow, Colors::Red);
		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

		circle->AddComponent(transform);
		circle->AddComponent(sprite);
		circle->AddComponent(physics);
		circle->AddComponent(collider);
		circle->AddComponent(colorChange);
		circle->AddComponent(screenWrap);

		GameObjectFactory::GetInstance().SaveObjectToFile(circle);

		return circle;
	}

	GameObject* CreateRectangle(Mesh* mesh)
	{
		GameObject* rectangle = new GameObject("Rectangle");

		Transform* transform = new Transform(0.0f, 0.0f);
		transform->SetScale(Vector2D(250.0f, 100.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);

		Physics* physics = new Physics();

		ColliderRectangle* collider = new ColliderRectangle(transform->GetScale() / 2);

		Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Green, Colors::Red);
		Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

		rectangle->AddComponent(transform);
		rectangle->AddComponent(sprite);
		rectangle->AddComponent(physics);
		rectangle->AddComponent(collider);
		rectangle->AddComponent(colorChange);
		rectangle->AddComponent(screenWrap);

		GameObjectFactory::GetInstance().SaveObjectToFile(rectangle);

		return rectangle;
	}

	GameObject* CreateTilemapObject(Mesh* mesh, SpriteSource* spriteSource, Tilemap* map)
	{
		GameObject* tilemap = new GameObject("Tilemap");

		Transform* transform = new Transform(-350.0f, 250.0f);
		transform->SetScale(Vector2D(100.0f, 100.0f));

		SpriteTilemap* spritetilemap = new SpriteTilemap();
		spritetilemap->SetMesh(mesh);
		spritetilemap->SetSpriteSource(spriteSource);
		spritetilemap->SetTilemap(map);

		ColliderTilemap* collider = new ColliderTilemap();
		collider->SetTilemap(map);

		tilemap->AddComponent(transform);
		tilemap->AddComponent(spritetilemap);
		tilemap->AddComponent(collider);

		GameObjectFactory::GetInstance().SaveObjectToFile(tilemap);

		return tilemap;

	}

	GameObject* CreateCollectible(Mesh* mesh, SpriteSource* spriteSource, Vector2D pos)
	{
		GameObject* collectible = new GameObject("Collectible");

		Transform* transform = new Transform(pos.x, pos.y);
		transform->SetScale(Vector2D(50.0f, 50.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);
		sprite->SetColor(Colors::Yellow);

		ColliderCircle* collider = new ColliderCircle(25.0f);

		collectible->AddComponent(transform);
		collectible->AddComponent(sprite);
		collectible->AddComponent(collider);

		GameObjectFactory::GetInstance().SaveObjectToFile(collectible);

		return collectible;

	}

	GameObject* CreateHazard(Mesh* mesh, SpriteSource* spriteSource, Vector2D pos)
	{
		GameObject* hazard = new GameObject("Hazard");

		Transform* transform = new Transform(pos.x, pos.y);
		transform->SetScale(Vector2D(25.0f, 50.0f));

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		ColliderRectangle* collider = new ColliderRectangle(transform->GetScale() / 2.0f);

		hazard->AddComponent(transform);
		hazard->AddComponent(sprite);
		hazard->AddComponent(collider);

		GameObjectFactory::GetInstance().SaveObjectToFile(hazard);

		return hazard;
	}

	GameObject* CreateEnemy(Mesh* mesh, SpriteSource* spriteSource, Vector2D pos)
	{
		GameObject* enemy = new GameObject("Enemy");

		Transform* transform = new Transform(pos.x, pos.y);
		transform->SetScale(Vector2D(100.0f, 100.0f));

		Physics* physics = new Physics();

		Sprite* sprite = new Sprite();
		sprite->SetMesh(mesh);
		sprite->SetSpriteSource(spriteSource);

		ColliderRectangle* collider = new ColliderRectangle(transform->GetScale() / 2.0f);

		//Behaviors::Enemy* enemyBehavior = new Behaviors::Enemy();

		enemy->AddComponent(transform);
		enemy->AddComponent(physics);
		enemy->AddComponent(sprite);
		enemy->AddComponent(collider);
		//enemy->AddComponent(enemyBehavior);

		GameObjectFactory::GetInstance().SaveObjectToFile(enemy);

		return enemy;
	}
}