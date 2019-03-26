//------------------------------------------------------------------------------
//
// File Name:	SpriteText.h
// Author(s):	Bar Ben-zvi
// Project:		Game Project 1
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once


#include "Sprite.h"
#include "Vector2D.h"


class SpriteText : public Sprite
{
public:
	//Default Constructor for this class
	SpriteText();

	// Clone the sprite, returning a dynamically allocated copy.
	Component* Clone() const override;

	// Draw a sprite (Sprite can be textured or untextured).
	void Draw() override;

	// Sets the tilemap data that will be used by the sprite.
	// Params:
	//   map = A pointer to the tilemap resource.
	void SetString(std::string newString);

private:

	std::string text;

};
