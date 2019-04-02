//------------------------------------------------------------------------------
//
// File Name:	WinSlot.h
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
// Brief:		Header file for the WinSlot class
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Component.h"



namespace Behaviors
{
	class WinSlot : public Component
	{
	public:

		WinSlot();

		Component* Clone() const override;

		bool GetContainsFrog() const;

		void SetContainsFrog(bool newContainsFrog);

	private:

		bool containsFrog;

	};
}