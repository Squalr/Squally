#pragma once
#include <string>

class LogUtils
{
public:
	static void redirectStandardOutputToFile();
	static void log(std::string info);
	static void logError(std::string errorInfo);

private:
	static std::string getLogFilePath();
	static std::string getErrorFilePath();

	static const std::string logFileName;
	static const std::string errorFileName;
};
