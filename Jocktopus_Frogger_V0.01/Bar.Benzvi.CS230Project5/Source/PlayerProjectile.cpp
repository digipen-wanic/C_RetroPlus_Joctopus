
#include "stdafx.h"
#include "PlayerProjectile.h"
#include "Collider.h"
#include "GameObject.h"
#include "Engine.h"
#include "Asteroid.h"
#include "PlayerShip.h"
#include "Physics.h"

namespace Behaviors
{
	PlayerProjectile::PlayerProjectile()
		: Component("PlayerProjectile")
	{

	}

	/*PlayerProjectile::~PlayerProjectile()
	{
	}*/

	static void CollisionHandlerBullet(GameObject& bullet, GameObject& other)
	{


		if (other.GetName() == "Asteroid")
		{
			bullet.GetComponent<PlayerProjectile>()->player->IncreaseScore(other.GetComponent<Asteroid>()->GetPointValue());
			bullet.Destroy();
		}
	}

	void PlayerProjectile::Initialize()
	{
		Collider* collider = GetOwner()->GetComponent<Collider>();
		collider->SetCollisionHandler(&CollisionHandlerBullet);

	}

	/*void PlayerProjectile::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		GetOwner()->GetComponent<Physics>()->SetVelocity(origVelocity * speedMod);
	}*/

	Component* PlayerProjectile::Clone() const
	{
		return new PlayerProjectile(*this);
	}

	/*void PlayerProjectile::Serialize(Parser& parser) const
	{
		UNREFERENCED_PARAMETER(parser);
	}

	void PlayerProjectile::Deserialize(Parser& parser)
	{
		UNREFERENCED_PARAMETER(parser);
	}*/

	void PlayerProjectile::SetSpawner(PlayerShip* playerComponent)
	{
		player = playerComponent;
	}

	

}