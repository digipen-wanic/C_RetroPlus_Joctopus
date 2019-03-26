

#include "stdafx.h"
#include "Asteroid.h"
#include "Engine.h"
#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"
#include "Collider.h"
#include "Random.h"
#include "Graphics.h"
#include "ColliderCircle.h"
#include "Space.h"
#include "GameObjectManager.h"
#include "Parser.h"


namespace Behaviors
{


	Asteroid::Asteroid(float speedMin, float speedMax, unsigned basePointsValue, float sizePointsModifier, float spawnScaleModifier)
		: Component("Asteroid"), speedMin(speedMin), speedMax(speedMax), basePointsValue(basePointsValue), sizePointsModifier(sizePointsModifier), 
		spawnScaleModifier(spawnScaleModifier), size(SizeLarge), location(LocationTopLeft)
	{

	}

	/*Asteroid::~Asteroid()
	{
		
	}*/

	Component* Asteroid::Clone() const
	{
		return new Asteroid(*this);
	}

	static void CollisionHandlerAsteroid(GameObject& asteroid, GameObject& otherObject)
	{

		if (otherObject.GetName() == "Bullet" || otherObject.GetName() == "Spaceship")
		{
			asteroid.GetComponent<Asteroid>()->SpawnNewAsteroids();
			asteroid.Destroy();
		}
	}

	void Asteroid::Initialize()
	{
		physics = GetOwner()->GetComponent<Physics>();
		transform = GetOwner()->GetComponent<Transform>();

		Collider* collider = GetOwner()->GetComponent<Collider>();
		collider->SetCollisionHandler(&CollisionHandlerAsteroid);

		SetPosition();
		SetVelocity();
	}

	/*void Asteroid::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		physics->SetVelocity(origVelocity * speedMod);
	}*/


	void Asteroid::Serialize(Parser& parser) const
	{
		parser.WriteVariable("speedMin", speedMin);
		parser.WriteVariable("speedMax", speedMax);
		parser.WriteVariable("basePointsValue", basePointsValue);
		parser.WriteVariable("sizePointsModifier", sizePointsModifier);
		parser.WriteVariable("spawnScaleModifier", spawnScaleModifier);
	}

	void Asteroid::Deserialize(Parser& parser)
	{
		parser.ReadVariable("speedMin", speedMin);
		parser.ReadVariable("speedMax", speedMax);
		parser.ReadVariable("basePointsValue", basePointsValue);
		parser.ReadVariable("sizePointsModifier", sizePointsModifier);
		parser.ReadVariable("spawnScaleModifier", spawnScaleModifier);
	}

	unsigned Asteroid::GetPointValue() const
	{
		if (size == SizeLarge)
		{
			return basePointsValue;
		}
		else if (size == SizeMedium)
		{
			return static_cast<unsigned>(basePointsValue * sizePointsModifier);
		}
		else
		{
			return static_cast<unsigned>(basePointsValue * (sizePointsModifier * sizePointsModifier));
		}
	}


	

	void Asteroid::SetPosition()
	{

		BoundingRectangle dimensions = Graphics::GetInstance().GetScreenWorldDimensions();

		if (size == SizeLarge)
		{
			int rand = RandomRange(0, 3);

			switch (rand)
			{
				case 0:
					transform->SetTranslation(Vector2D(dimensions.left + transform->GetScale().x, dimensions.top - transform->GetScale().y));
					break;
				case 1:
					transform->SetTranslation(Vector2D(dimensions.left + transform->GetScale().x, dimensions.bottom + transform->GetScale().y));
					break;
				case 2:
					transform->SetTranslation(Vector2D(dimensions.right - transform->GetScale().x, dimensions.top - transform->GetScale().y));
					break;
				case 3:
					transform->SetTranslation(Vector2D(dimensions.right - transform->GetScale().x, dimensions.bottom + transform->GetScale().y));
					break;
			}
		}
	}

	void Asteroid::SetVelocity()
	{
		float randAngle = RandomRange(0.0f, 360.0f);
		float randSpeed = RandomRange(speedMin, speedMax);

		physics->SetVelocity(Vector2D::FromAngleDegrees(randAngle) * randSpeed);
	}


	void Asteroid::SpawnNewAsteroids()
	{

		if (size == SizeLarge)
		{
			size = SizeMedium;
			transform->SetScale(transform->GetScale() * spawnScaleModifier);
			GetOwner()->GetComponent<ColliderCircle>()->SetRadius(GetOwner()->GetComponent<ColliderCircle>()->GetRadius() * spawnScaleModifier);
			int randCount = RandomRange(2, 4);

			for (int i = 0; i < randCount; i++)
			{
				GameObject* newAsteroid = new GameObject(*GetOwner());
				GetOwner()->GetSpace()->GetObjectManager().AddObject(*newAsteroid);
			}
		}
		else if (size == SizeMedium)
		{
			size = SizeSmall;
			transform->SetScale(transform->GetScale() * spawnScaleModifier);
			GetOwner()->GetComponent<ColliderCircle>()->SetRadius(GetOwner()->GetComponent<ColliderCircle>()->GetRadius() * spawnScaleModifier);
			int randCount = RandomRange(1, 3);

			for (int i = 0; i < randCount; i++)
			{
				GameObject* newAsteroid = new GameObject(*GetOwner());
				GetOwner()->GetSpace()->GetObjectManager().AddObject(*newAsteroid);
			}
		}
	}
}