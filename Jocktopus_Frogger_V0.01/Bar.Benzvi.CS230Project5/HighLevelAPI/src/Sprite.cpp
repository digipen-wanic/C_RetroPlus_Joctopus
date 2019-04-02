//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------



#include "stdafx.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "MeshHelper.h"
#include "Mesh.h"
#include "Graphics.h"
#include "Transform.h"
#include "Matrix2DStudent.h"
#include "GameObject.h"
#include "Parser.h"

Sprite::Sprite()
	: Component("Sprite"), frameIndex(0), spriteSource(nullptr), mesh(nullptr), color(Colors::White)
{

}

Component* Sprite::Clone() const
{
	return new Sprite(*this);
}

void Sprite::Initialize()
{
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
}

void Sprite::Draw()
{
	Draw(Vector2D(0.0f, 0.0f));
}


void Sprite::Draw(const Vector2D& offset)
{
	if (mesh == nullptr || transform == nullptr)
	{
		return;
	}

	if (spriteSource != nullptr)
	{
		Vector2D textureCoords;
		spriteSource->GetUV(frameIndex, textureCoords);

		Graphics::GetInstance().SetTexture(spriteSource->GetTexture(), textureCoords);
	}
	else
	{
		Graphics::GetInstance().SetTexture(nullptr);
	}


	Matrix2D translation = Matrix2D::TranslationMatrix(offset.x, offset.y);
	Graphics::GetInstance().SetTransform(translation * reinterpret_cast<const Matrix2D&>(transform->GetMatrix()));

	Graphics::GetInstance().SetSpriteBlendColor(color);

	mesh->Draw();
}

void Sprite::SetAlpha(float alpha)
{
	color.a = alpha;
}

float Sprite::GetAlpha() const
{
	return color.a;
}

// Loads object data from a file.
void Sprite::Deserialize(Parser& parser)
{
	parser.ReadVariable("frameIndex", frameIndex);
	parser.ReadVariable("color", color);
}

// Saves object data to a file.
void Sprite::Serialize(Parser& parser) const
{
	parser.WriteVariable("frameIndex", frameIndex);
	parser.WriteVariable("color", color);
}

void Sprite::SetFrame(unsigned int frameIndex_)
{
	UNREFERENCED_PARAMETER(frameIndex_);
	if (spriteSource == nullptr)
	{
		return;
	}

	if (frameIndex_ < spriteSource->GetFrameCount())
	{
		frameIndex = frameIndex_;
	}

}

unsigned Sprite::GetFrame() const
{
	return frameIndex;
}

void Sprite::SetMesh(Mesh* mesh_)
{
	mesh = mesh_;
}

void Sprite::SetSpriteSource(SpriteSource* spriteSource_)
{
	spriteSource = spriteSource_;
}

SpriteSource * Sprite::GetSpriteSource() const
{
	return spriteSource;
}

void Sprite::SetColor(Color color_)
{
	color = color_;
}

const Color& Sprite::GetColor() const
{
	return color;
}