//------------------------------------------------------------------------------
//
// File Name:	SpriteText.cpp
// Author(s):	Bar Ben-zvi
// Project:		Game Project 1
// Course:		WANIC VGP2 2018-2019
//
// Brief: Cpp file for the spritext class, which displays a given string.
//
// Copyright © 2018 DigiPen (USA) Corporation.
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

void SpriteText::Initialize()
{
	Sprite::Initialize();
	cases.push_back(SpecialCase('I', Vector2D(-4.0f, 0.0f)));
}

void SpriteText::Draw()
{
	Vector2D currOffset(0, 0);
	Vector2D specialOffset(0, 0);
	Vector2D nextSpecialOffset(0, 0);
	Vector2D scale = transform->GetScale();

	float xOffset = 0;

	size_t textCount = text.length();

	//Set the xOffset based off of our alignment
	if (alignment == CENTER)
	{
		xOffset = -scale.x * textCount / 2;
	}
	else if (alignment == RIGHT)
	{
		xOffset = -scale.x * textCount;
	}

	currOffset.x = xOffset;

	//"Print" all characters in our string
	for (size_t i = 0; i < textCount; ++i)
	{
		int asciiVal = text[i];

		for (auto it = cases.cbegin(); it != cases.cend(); ++it)
		{
			if ((*it).caseLetter == text[i])
			{
				specialOffset = (*it).caseOffset;
				nextSpecialOffset = (*it).caseOffset;
				break;
			}
		}

		if (specialOffset.MagnitudeSquared() == 0.0f)
		{
			currOffset += nextSpecialOffset;
			nextSpecialOffset.x = 0.0f;
			nextSpecialOffset.y = 0.0f;
		}

		currOffset += specialOffset;

		//If the current character is a number
		if (asciiVal < 58 && asciiVal > 47)
		{
			SetFrame(asciiVal - 48);
			Sprite::Draw(currOffset);

			
		}
		//If the current character is an uppercase letter
		else if (asciiVal < 91 && asciiVal > 64)
		{
			SetFrame(asciiVal - 55);
			Sprite::Draw(currOffset);
		}

		currOffset.x += scale.x;

		specialOffset.x = 0.0f;
		specialOffset.y = 0.0f;

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
