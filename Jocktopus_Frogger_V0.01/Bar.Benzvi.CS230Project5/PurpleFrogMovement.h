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
		PurpleFrogMovement();
	private:
		float time;
	};

}