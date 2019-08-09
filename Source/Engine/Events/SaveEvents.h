#pragma once
#include <string>

class SaveEvents
{
public:
	static void TriggerSoftSaveGameState();

	static const std::string EventSoftSaveGameState;
};
