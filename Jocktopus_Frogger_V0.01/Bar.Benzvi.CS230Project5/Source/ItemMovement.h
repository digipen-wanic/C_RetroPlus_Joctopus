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
		/*
		Makes a Item Move
		Takes: speed to tell how fast to move, left to tell if it is moving left
		*/
		ItemMovement(float speed = 20.0, int dir = -1);
		/*
		Makes a clone on ItemMovement
		*/
		Component* Clone() const override;
		/*
		sets transform
		*/
		void Initialize() override;
		/*
		moves based on speed
		Takes: time
		*/
		void Update(float dt) override;
		/*
		Sets speed
		Takes: Speed
		*/
		void SetSpeed(float Speed);
		/*
		Get speed
		Returns: Speed
		*/
		float GetSpeed();
		/*
		Sets the x direction this item will move in
		Takes: int
		*/
		void SetDirection(int dir);
		/*
		Gets the x direction this item is moving in
		Returns: int
		*/
		int GetDirection() const;

	private:
		int direction;
		Transform* transform;
		float speed;
	};
}
