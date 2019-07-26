#pragma once
#include <string>

class DeveloperModeEvents
{
public:
	static const std::string EventDeveloperModeModeEnable;
	static const std::string EventDeveloperModeModeDisable;

	static void TriggerDeveloperModeModeEnable();
	static void TriggerDeveloperModeModeDisable();
};
