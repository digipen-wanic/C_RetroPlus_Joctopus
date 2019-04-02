/*
By: Kyle Jamison
PurpleFrogMovement
3/28/19
Purple Frog Movment
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

	class PurpleFrogMovement : public Component
	{
	public:
		/*
		Make a PFrog
		*/
		PurpleFrogMovement(float delay = 1, float speed = 30, int direction = 1);
		/*
		Make a clone
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
		// Runs whenever a collision is detected
		friend void PFrogCollisionHandler(GameObject& object, GameObject& other);
		/*
		sets the direction
		Takes: int for pos or neg
		*/
		void SetDirection(int dir);

		void SetOnLog(bool dir);

	private:
		float delay;
		float timer;
		float speed;
		Transform* transform;
		int direction;
		bool onLog;
		bool fellOff; 
		bool fixed;
	};

}