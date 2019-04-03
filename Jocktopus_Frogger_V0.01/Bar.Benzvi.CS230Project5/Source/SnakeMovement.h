/*
By: Kyle Jamison
SnakeMovement
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

	class SnakeMovement : public Component
	{
	public:
		/*
		Make a PFrog
		*/
		SnakeMovement(float speed = 50, int direction = 1, bool flaot = false);
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
		friend void SnakeCollisionHandler(GameObject& object, GameObject& other);
		/*
		sets the direction
		Takes: int for pos or neg
		*/
		void SetDirection(int dir);

		int GetDirection();

		void SetOnLog(bool log);

	private:
		float speed;
		Transform* transform;
		int direction;
		bool onLog;
		bool floats;
	};

}