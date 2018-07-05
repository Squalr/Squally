#pragma once
#include <string>
#include <locale>         
#include <sstream> 

#include "cocos2d.h"


using namespace cocos2d;

class StrUtils
{
public:
	static std::vector<std::string>* tokenize(std::string str, std::string delimiters);
	static std::vector<std::string>* splitOn(std::string str, std::string delimiter);
	static std::string toStringZeroPad(int value, int zeroCount);
	static std::string quote(std::string value);
	static bool isInteger(std::string str);
	static bool isFloat(std::string str);
	static bool isHexNumber(std::string str);
	static bool startsWith(std::string str, std::string prefix, bool ignoreCase);
	static bool endsWith(std::string str, std::string suffix, bool ignoreCase);
	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
};

