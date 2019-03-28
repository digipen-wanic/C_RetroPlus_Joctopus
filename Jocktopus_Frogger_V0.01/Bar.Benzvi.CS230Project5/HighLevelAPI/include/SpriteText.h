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

enum TextAlignment {CENTER, LEFT, RIGHT};

class SpriteText : public Sprite
{
public:
	//Default Constructor for this class
	SpriteText();

	// Clone the sprite, returning a dynamically allocated copy.
	Component* Clone() const override;

	// Draw a sprite (Sprite can be textured or untextured).
	void Draw() override;

	// Sets the string that will be used by the sprite.
	// Params:
	//   newString = The string that this sprite will draw.
	void SetString(std::string newString);

	// Sets the alignment of this sprite.
	// Params:
	//	newAlignment = the new alignment of this spritetext
	void SetAlignment(TextAlignment newAlignment);

private:

	std::string text;

	TextAlignment alignment;

};
