#pragma once
#include <string>

class PlatformerEntity;
class MinMaxPool;

class HelperEvents
{
public:
	static const std::string EventFindScrappy;
	static const std::string EventRequestPickPocket;

	struct RequestPickPocketArgs
	{
		PlatformerEntity* target;
		MinMaxPool* pocketPool;
		std::string saveKeyPickPocketed;

		RequestPickPocketArgs(PlatformerEntity* target, MinMaxPool* pocketPool, std::string saveKeyPickPocketed) : target(target), pocketPool(pocketPool), saveKeyPickPocketed(saveKeyPickPocketed)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerRequestPickPocket(RequestPickPocketArgs args);
};
