#pragma once

#include <string>

class LocalizedString;

class Gold
{
public:

	static std::string getIdentifier();
	static std::string getIconResource();
	static LocalizedString* getString();
};
