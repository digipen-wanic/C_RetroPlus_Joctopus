//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "SpriteSource.h"
#include "Vector2D.h"

SpriteSource::SpriteSource(int numCols, int numRows, Texture* texture)
	: numRows(numRows), numCols(numCols), texture(texture)
{

}


Texture* SpriteSource::GetTexture() const
{
	return texture;
}

unsigned SpriteSource::GetFrameCount() const
{
	return numRows * numCols;
}

void SpriteSource::GetUV(unsigned int frameIndex, Vector2D& textureCoords) const
{
	unsigned int currRow = frameIndex / numCols;

	unsigned int currCol = frameIndex % numCols;

	textureCoords.x = (1.0f / numCols) * currCol;
	textureCoords.y = (1.0f / numRows) * currRow;
}