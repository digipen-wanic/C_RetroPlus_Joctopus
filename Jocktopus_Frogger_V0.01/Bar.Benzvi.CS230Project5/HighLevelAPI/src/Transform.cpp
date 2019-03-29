//------------------------------------------------------------------------------
//
// File Name:	Transform.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "Transform.h"
#include "Matrix2DStudent.h"
#include "Parser.h"


Transform::Transform(float x, float y)
	: Component("Transform"), translation(x, y), scale(Vector2D(50.0f, 50.0f)), rotation(0), isDirty(true)
{
}

Transform::Transform(Vector2D translation, Vector2D scale, float rotation)
	: Component("Transform"), translation(translation), scale(scale), rotation(rotation)
{
}

Component* Transform::Clone() const
{
	return new Transform(*this);
}

const CS230::Matrix2D& Transform::GetMatrix()
{
	//If our transform is dirty, recalculate the transform matrix
	if (isDirty)
	{
		CalculateMatrices();
	}

	return matrix;
}

const CS230::Matrix2D& Transform::GetInverseMatrix()
{
	if (isDirty)
	{
		CalculateMatrices();
	}

	return inverseMatrix;
}

void Transform::SetTranslation(const Vector2D& translation_)
{
	if (!AlmostEqual(translation, translation_))
	{
		translation = translation_;
		isDirty = true;
	}
	
}

const Vector2D& Transform::GetTranslation() const
{
	return translation;
}

void Transform::SetRotation(float rotation_)
{
	if (!AlmostEqual(rotation, rotation_))
	{
		rotation = rotation_;
		isDirty = true;
	}
	
	
}

float Transform::GetRotation() const
{
	return rotation;
}

void Transform::SetScale(const Vector2D& scale_)
{
	if (!AlmostEqual(scale, scale_))
	{
		scale = scale_;
		isDirty = true;
	}
}

const Vector2D& Transform::GetScale() const
{
	return scale;
}

// Loads object data from a file.
void Transform::Deserialize(Parser& parser)
{
	parser.ReadVariable("translation", translation);
	parser.ReadVariable("rotation", rotation);
	parser.ReadVariable("scale", scale);
}

// Saves object data to a file.
void Transform::Serialize(Parser& parser) const
{
	parser.WriteVariable("translation", translation);
	parser.WriteVariable("rotation", rotation);
	parser.WriteVariable("scale", scale);
}

void Transform::CalculateMatrices()
{
	CS230::Matrix2D matrixT = CS230::Matrix2D::TranslationMatrix(translation.x, translation.y);
	CS230::Matrix2D matrixS = CS230::Matrix2D::ScalingMatrix(scale.x, scale.y);
	CS230::Matrix2D matrixR = CS230::Matrix2D::RotationMatrixRadians(rotation);

	CS230::Matrix2D invMatrixT = CS230::Matrix2D::TranslationMatrix(-translation.x, -translation.y);
	CS230::Matrix2D invMatrixS = CS230::Matrix2D::ScalingMatrix(1.0f / scale.x, 1.0f / scale.y);
	CS230::Matrix2D invMatrixR = CS230::Matrix2D::RotationMatrixRadians(-rotation);

	matrix = matrixT * matrixR * matrixS;
	inverseMatrix = invMatrixS * invMatrixR * invMatrixT;

	isDirty = false;
}
