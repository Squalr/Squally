#include "LogUtils.h"

const std::string LogUtils::logFileName = "SquallyLogs.txt";
const std::string LogUtils::errorFileName = "SquallyErrors.txt";

void LogUtils::redirectStandardOutputToFile()
{
	freopen(LogUtils::getLogFilePath().c_str(), "w", stdout);
	freopen(LogUtils::getErrorFilePath().c_str(), "w", stderr);
}

std::string LogUtils::getLogFilePath()
{
	return cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + LogUtils::logFileName;
}

std::string LogUtils::getErrorFilePath()
{
	return cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + LogUtils::errorFileName;
}
