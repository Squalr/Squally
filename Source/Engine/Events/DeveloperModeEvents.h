#pragma once
#include <string>

class DeveloperModeEvents
{
public:
	static const std::string EventDeveloperModeModeEnable;
	static const std::string EventDeveloperModeModeDisable;

	struct DeveloperModeEnableArgs
	{
		int debugLevel = 0;

		DeveloperModeEnableArgs(int debugLevel) : debugLevel(debugLevel) { }
	};

	static void TriggerDeveloperModeModeEnable(DeveloperModeEnableArgs args);
	static void TriggerDeveloperModeModeDisable();
};
