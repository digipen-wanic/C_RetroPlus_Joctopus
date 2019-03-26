//------------------------------------------------------------------------------
//
// File Name:	SpriteTilemap.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Tilemap.h"
#include "SpriteTilemap.h"
#include "Sprite.h"
#include "Transform.h"
#include "Parser.h"



SpriteTilemap::SpriteTilemap()
	: map(nullptr)
{

}

Component* SpriteTilemap::Clone() const
{
	return new SpriteTilemap(*this);
}

void SpriteTilemap::Draw()
{

	unsigned height = map->GetHeight();
	unsigned width = map->GetWidth();

	Vector2D scale = transform->GetScale();

	for (unsigned i = 0; i < height; ++i)
	{
		for (unsigned j = 0; j < width; ++j)
		{
			int value = map->GetCellValue(j, i);

			if (value != 0)
			{
				SetFrame(value - 1);
				Vector2D offset(j * scale.x, i * -scale.y);
				Sprite::Draw(offset);
			}

		}
	}

}

void SpriteTilemap::SetTilemap(const Tilemap* map_)
{
	map = map_;
}