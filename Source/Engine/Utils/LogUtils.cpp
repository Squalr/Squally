#include "LogUtils.h"

#include <iostream>

#include "cocos/platform/CCFileUtils.h"

const std::string LogUtils::logFileName = "SquallyLogs.txt";
const std::string LogUtils::errorFileName = "SquallyErrors.txt";

bool LogUtils::redirectStandardOutputToFile()
{
	return (stdout == freopen(LogUtils::getLogFilePath().c_str(), "w", stdout))
		&& (stderr == freopen(LogUtils::getErrorFilePath().c_str(), "w", stderr));
}

void LogUtils::log(std::string info)
{
	std::cout << info << std::endl;
}

void LogUtils::logError(std::string errorInfo)
{
	std::cerr << errorInfo << std::endl;
}

std::string LogUtils::getLogFilePath()
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + LogUtils::logFileName;
}

std::string LogUtils::getErrorFilePath()
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + LogUtils::errorFileName;
}
