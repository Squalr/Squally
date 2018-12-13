#pragma once
#include <string>

class DeveloperModeEvents
{
public:
	static void TriggerDeveloperModeModeEnable();
	static void TriggerDeveloperModeModeDisable();

	static const std::string DeveloperModeModeEnableEvent;
	static const std::string DeveloperModeModeDisableEvent;
};
