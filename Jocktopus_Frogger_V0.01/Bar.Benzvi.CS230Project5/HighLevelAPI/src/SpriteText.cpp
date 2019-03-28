//------------------------------------------------------------------------------
//
// File Name:	SpriteText.cpp
// Author(s):	Bar Ben-zvi
// Project:		Game Project 1
// Course:		WANIC VGP2 2018-2019
//
// Brief: Header file for the spritext class, which displays a given string.
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteText.h"
#include "Transform.h"

SpriteText::SpriteText()
	: text(""), alignment(CENTER)
{

}


Component* SpriteText::Clone() const
{
	return new SpriteText(*this);
}

void SpriteText::Draw()
{
	Vector2D currOffset(0, 0);
	Vector2D scale = transform->GetScale();

	size_t textCount = text.length();

	if (alignment == CENTER)
	{
		currOffset.x = -scale.x * textCount / 2;
	}
	else if (alignment == RIGHT)
	{
		currOffset.x = -scale.x * textCount;
	}

	for (size_t i = 0; i < textCount; ++i)
	{
		int asciiVal = text[i];

		if (asciiVal < 58 && asciiVal > 47)
		{
			SetFrame(asciiVal - 48);
			Sprite::Draw(currOffset);

			currOffset.x += scale.x;
		}
	}

}

void SpriteText::SetString(std::string newString)
{
	text = newString;
}

void SpriteText::SetAlignment(TextAlignment newAlignment)
{
	alignment = newAlignment;
}
