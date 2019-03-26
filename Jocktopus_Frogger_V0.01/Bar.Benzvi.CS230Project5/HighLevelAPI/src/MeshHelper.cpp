//------------------------------------------------------------------------------
//
// File Name:	MeshHelper.cpp
// Author(s):	Bar Ben-zvi
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "MeshHelper.h"
#include "MeshFactory.h"
#include "Vertex.h"


Mesh* CreateTriangleMesh(const Color& color0, const Color& color1, const Color& color2)
{

	MeshFactory::GetInstance().AddTriangle(Vertex(Vector2D(-0.5, 0.5), color2), Vertex(Vector2D(-0.5, -0.5), color0), Vertex(Vector2D(0.5, 0), color1));

	return MeshFactory::GetInstance().EndCreate();

}

Mesh* CreateQuadMesh(const Vector2D& textureSize, const Vector2D& extents)
{
	Vertex shared1(Vector2D(extents.x, -extents.y), textureSize);
	Vertex shared2(Vector2D(-extents.x, extents.y), Vector2D(0, 0));

	MeshFactory::GetInstance().AddTriangle(shared1, shared2, Vertex(extents, Vector2D(textureSize.x, 0)));
	MeshFactory::GetInstance().AddTriangle(shared1, shared2, Vertex(-extents, Vector2D(0, textureSize.y)));

	return MeshFactory::GetInstance().EndCreate();
}