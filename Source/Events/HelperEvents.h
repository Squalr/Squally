#pragma once
#include <string>

class PlatformerEntity;

class HelperEvents
{
public:
	static const std::string EventFindScrappy;
	static const std::string EventRequestPickPocket;

	struct RequestPickPocketArgs
	{
		PlatformerEntity* target;

		RequestPickPocketArgs(PlatformerEntity* target) : target(target)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerRequestPickPocket(RequestPickPocketArgs args);
};
