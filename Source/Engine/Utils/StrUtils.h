#pragma once
#include <string>
#include <vector>

class StrUtils
{
public:
	static int unicodeStrLen(std::string str);
	static std::vector<std::string> tokenize(std::string str, std::string delimiters);
	static std::vector<std::string> splitOn(std::string str, std::string delimiter);
	static std::string toStringZeroPad(int value, int zeroCount);
	static std::string quote(std::string value);
	static bool isInteger(std::string str);
	static bool isFloat(std::string str);
	static bool isHexNumber(std::string str);
	static bool isRegexMatch(const std::string str, const std::string regex);
	static std::string ltrim(std::string str, std::string toRemove, bool ignoreCase = false);
	static std::string rtrim(std::string str, std::string toRemove, bool ignoreCase = false);
	static std::string trim(std::string str, std::string toRemove, bool ignoreCase = false);
	static bool startsWith(std::string str, std::string prefix, bool ignoreCase);
	static bool endsWith(std::string str, std::string suffix, bool ignoreCase);
	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
	static std::string replaceFirstOccurence(std::string str, const std::string& from, const std::string& to);
};
