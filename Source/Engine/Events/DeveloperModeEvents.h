#pragma once
#include <string>

class DeveloperModeEvents
{
public:
	static const std::string EventDeveloperModeModeEnable;
	static const std::string EventDeveloperModeModeDisable;

	struct DeveloperModeEnableArgs
	{
		int debugLevel;

		DeveloperModeEnableArgs(int debugLevel) : debugLevel(debugLevel) { }
	};

	static void TriggerDeveloperModeModeEnable(DeveloperModeEnableArgs args);
	static void TriggerDeveloperModeModeDisable();
};
