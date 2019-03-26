

#include "stdafx.h"
#include "Parser.h"


ParseException::ParseException(const std::string& fileName, const std::string& errorDetails)
	: std::exception(("Error reading file " + fileName + ". " + errorDetails).c_str())
{
	
}

Parser::Parser(const std::string& filename, std::ios_base::openmode mode)
	: stream(filename, mode), filename(filename), indentLevel(0)
{

}

// Closes the currently open file.
Parser::~Parser()
{
	stream.close();
}

// Begins a new scope when writing to a file.
// Outputs a curly brace and increases the tab count.
void Parser::BeginScope()
{
	CheckFileOpen();

	for (unsigned i = 0; i < indentLevel; ++i)
	{
		stream << tab;
	}
	stream << "{" << std::endl;
	++indentLevel;
}

// Ends the current scope when writing to a file.
// Outputs an end curly brace and decreases tab count.
void Parser::EndScope()
{
	CheckFileOpen();

	--indentLevel;
	for (unsigned i = 0; i < indentLevel; ++i)
	{
		stream << tab;
	}
	stream << "}" << std::endl;
}

void Parser::ReadSkip(const std::string& text)
{
	CheckFileOpen();

	std::string nextWord;

	stream >> nextWord;

	if (text != nextWord)
	{
		throw ParseException(filename, "Given name could not be found");
	}
}

void Parser::ReadSkip(char delimiter)
{
	stream.ignore(10, delimiter);
}

void Parser::CheckFileOpen()
{
	if (stream.is_open() == false)
	{
		throw ParseException(filename, "File named " + filename + " could not be opened");
	}
}
