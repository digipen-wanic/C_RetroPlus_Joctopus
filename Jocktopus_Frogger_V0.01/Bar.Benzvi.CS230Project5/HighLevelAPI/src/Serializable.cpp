//------------------------------------------------------------------------------
//
// File Name:	Serializable.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		CS230
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Parser.h"
#include "Serializable.h"


// Loads object data from a file.
void Serializable::Deserialize(Parser& parser)
{
	UNREFERENCED_PARAMETER(parser);
}

// Saves object data to a file.
void Serializable::Serialize(Parser& parser) const
{
	UNREFERENCED_PARAMETER(parser);
}

// These functions are protected to ensure this class is effectively abstract.
Serializable::Serializable()
{

}

Serializable::~Serializable()
{

}

Serializable::Serializable(const Serializable& other)
{
	UNREFERENCED_PARAMETER(other);
}

Serializable& Serializable::operator=(const Serializable& other)
{
	UNREFERENCED_PARAMETER(other);
	return *this;
}