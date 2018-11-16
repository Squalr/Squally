#pragma once
#include "cocos2d.h"

class LogUtils
{
public:
	static void redirectStandardOutputToFile();

private:
	static std::string getLogFilePath();
	static std::string getErrorFilePath();

	static const std::string logFileName;
	static const std::string errorFileName;
};
