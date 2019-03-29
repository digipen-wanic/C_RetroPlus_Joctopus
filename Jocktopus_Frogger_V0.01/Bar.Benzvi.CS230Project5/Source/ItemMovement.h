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
		ItemMovement(float speed = 20.0, bool left = true);
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
		Sets left to true or false
		Takes: bool
		*/
		void SetLeft(bool Left);
		/*
		Get left to true or false
		Returns: bool
		*/
		bool SetLeft();

	private:
		bool moveLeft;
		Transform* transform;
		float speed;
	};
}
