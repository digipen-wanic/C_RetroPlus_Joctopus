/*
By: Kyle Jamison
ItemMovement
3/27/19
Move the thing
*/
#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Transform.h" // Transform


//------------------------------------------------------------------------------

namespace Behaviors
{

	class ItemMovement : public Component
	{
	public:
		ItemMovement::ItemMovement(float speed = 1.0, bool left = true);

		void ItemMovement::Initialize();

		void ItemMovement::Update();

		void ItemMovement::SetSpeed(float Speed);

		void ItemMovement::SetLeft(bool Left);

	private:
		bool moveLeft;
		Transform* transform;
		float speed;
	};
}
