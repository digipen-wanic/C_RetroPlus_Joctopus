//------------------------------------------------------------------------------
//
// File Name:	Matrix2DStudent.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


#include "stdafx.h"

#include "Matrix2DStudent.h"



namespace CS230
{

	Matrix2D::Matrix2D()
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				m[i][j] = 0;
			}
		}
	}

	Matrix2D Matrix2D::IdentityMatrix()
	{
		Matrix2D matrix;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (i == j)
				{
					matrix.m[i][j] = 1;
				}
			}
		}

		return matrix;

	}

	Matrix2D Matrix2D::Transposed() const
	{
		Matrix2D matrix;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				matrix.m[i][j] = m[j][i];
			}
		}
		
		return matrix;
	}

	Matrix2D Matrix2D::TranslationMatrix(float x, float y)
	{
		Matrix2D matrix = IdentityMatrix();

		matrix.m[0][2] = x;
		matrix.m[1][2] = y;

		return matrix;
	}

	Matrix2D Matrix2D::ScalingMatrix(float x, float y)
	{
		Matrix2D matrix = IdentityMatrix();

		matrix.m[0][0] = x;
		matrix.m[1][1] = y;

		return matrix;
	}

	Matrix2D Matrix2D::RotationMatrixDegrees(float angle)
	{
		float radians = (angle * static_cast<float>(M_PI)) / 180;

		return RotationMatrixRadians(radians);

		
	}

	Matrix2D Matrix2D::RotationMatrixRadians(float angle)
	{
		Matrix2D matrix = IdentityMatrix();

		matrix.m[0][0] = cosf(angle);
		matrix.m[1][1] = cosf(angle);
		matrix.m[0][1] = -sinf(angle);
		matrix.m[1][0] = sinf(angle);

		return matrix;
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& other) const
	{
		Matrix2D final;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				final.m[i][j] = RowColumnMultiply(other, i, j);
			}
		}

		return final;
	}


	Matrix2D& Matrix2D::operator*=(const Matrix2D& other)
	{
		*this = *this * other;

		return *this;
	}

	Vector2D Matrix2D::operator*(const Vector2D& vec) const
	{
		Vector2D vector;
		vector.x = (m[0][0] * vec.x) + (m[0][1] * vec.y) + (m[0][2] * 1.0f);
		vector.y = (m[1][0] * vec.x) + (m[1][1] * vec.y) + (m[1][2] * 1.0f);
		
		return vector;
	}



	float Matrix2D::RowColumnMultiply(const Matrix2D& other, unsigned row, unsigned col) const
	{
		float product = (m[row][0] * other.m[0][col]) + (m[row][1] * other.m[1][col]) + (m[row][2] * other.m[2][col]);

		return product;
	}


}