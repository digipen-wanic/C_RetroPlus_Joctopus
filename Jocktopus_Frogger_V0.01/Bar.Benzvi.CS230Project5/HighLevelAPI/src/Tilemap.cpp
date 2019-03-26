//------------------------------------------------------------------------------
//
// File Name:	Tilemap.cpp
// Author(s):	Bar Ben-zvi
// Project:		BetaFramework
// Course:		WANIC VGP2
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Tilemap.h"
#include <fstream>

Tilemap::Tilemap(unsigned numColumns, unsigned numRows, int** data)
	: numColumns(numColumns), numRows(numRows), data(data)
{
}

Tilemap::~Tilemap()
{
	for (unsigned i = 0; i < numRows; ++i)
	{
		delete[] data[i];
	}

	delete[] data;
}

unsigned Tilemap::GetWidth() const
{
	return numColumns;
}

unsigned Tilemap::GetHeight() const
{
	return numRows;
}

int Tilemap::GetCellValue(unsigned column, unsigned row) const
{
	if (column >= numColumns || row >= numRows)
	{
		return -1;
	}
	else
	{
		return data[column][row];
	}
}

Tilemap* Tilemap::CreateTilemapFromFile(const std::string& filename)
{
	std::string fName = "Assets\\Levels\\" + filename;
	std::ifstream file(fName);

	if (file.is_open())
	{
		int columns = 0;
		int rows = 0;

		if (ReadIntegerVariable(file, "width", columns) && ReadIntegerVariable(file, "height", rows))
		{
			int** data = ReadArrayVariable(file, "data", columns, rows);

			if (data != nullptr)
			{

				std::cout << "width: " << columns << std::endl;
				std::cout << "height: " << rows << std::endl;

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < columns; j++)
					{
						std::cout << data[j][i] << " ";
					}
					std::cout << std::endl;
				}

				return new Tilemap(columns, rows, data);
			}
		}
	}

	return nullptr;

}

bool Tilemap::ReadIntegerVariable(std::ifstream& file, const std::string& name, int& variable)
{
	std::string nextWord;

	file >> nextWord;

	if (nextWord == name)
	{
		file >> variable;
		return true;
	}

	return false;
}

int** Tilemap::ReadArrayVariable(std::ifstream& file, const std::string& name, unsigned columns, unsigned rows)
{
	std::string nextWord;

	file >> nextWord;

	if (nextWord == name && columns != 0 && rows != 0)
	{
		int** array = new int*[columns];

		for (unsigned i = 0; i < columns; ++i)
		{
			array[i] = new int[rows];
		}

		for (unsigned i = 0; i < rows; ++i)
		{
			for (unsigned j = 0; j < columns; ++j)
			{
				file >> array[j][i];
			}
		}

		return array;
	}

	return nullptr;
}