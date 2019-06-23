#pragma once

#include <string>

class LocalizedString;

class Doubloons
{
public:

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();
};
