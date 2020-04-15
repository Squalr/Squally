#include "LogUtils.h"

#include <iostream>
#include <fstream>

#include "cocos/platform/CCFileUtils.h"

const std::string LogUtils::logFileName = "SquallyLogs.txt";
const std::string LogUtils::errorFileName = "SquallyErrors.txt";
std::string LogUtils::logFilePath = "";
std::string LogUtils::errorFilePath = "";

void LogUtils::initialize()
{
	LogUtils::logFilePath = LogUtils::getLogFilePath();
	LogUtils::errorFilePath = LogUtils::getErrorFilePath();

	LogUtils::clearLogs();
}

void LogUtils::log(std::string info)
{
	try
	{
		std::ofstream logFile = std::ofstream();

		logFile.open(LogUtils::logFilePath, std::ios_base::app);
		logFile << info;
		logFile << "\n";

		logFile.close();
	}
	catch (...)
	{
	}
}

void LogUtils::logError(std::string errorInfo)
{
	try
	{
		std::ofstream logFile = std::ofstream();

		logFile.open(LogUtils::errorFilePath, std::ios_base::app);
		logFile << errorInfo;
		logFile << "\n";

		logFile.close();
	}
	catch (...)
	{
	}
}

void LogUtils::clearLogs()
{
	try
	{
		std::ofstream logFile = std::ofstream();

		logFile.open(LogUtils::logFilePath, std::ofstream::out | std::ofstream::trunc);

		logFile.close();

		std::ofstream errorFile = std::ofstream();

		errorFile.open(LogUtils::errorFilePath, std::ofstream::out | std::ofstream::trunc);

		errorFile.close();
	}
	catch (...)
	{
	}
}

std::string LogUtils::getLogFilePath()
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + LogUtils::logFileName;
}

std::string LogUtils::getErrorFilePath()
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + LogUtils::errorFileName;
}
