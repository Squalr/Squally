#pragma once
#include "cocos2d.h"
#include "Gui/Components/Mouse.h"

using namespace cocos2d;

class StrUtils
{
public:
	static std::vector<std::string>* tokenize(std::string str, std::string delimiters);
	static std::vector<std::string>* splitOn(std::string str, std::string delimiter);
	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
};

