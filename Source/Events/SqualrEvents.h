#pragma once
#include <string>


class SqualrEvents
{
public:
	static const std::string EventDartCollided;
	static const std::string EventFireballCollided;

	static void TriggerDartCollided();
	static void TriggerFireballCollided();
};
