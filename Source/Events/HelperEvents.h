#pragma once
#include <functional>
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
		PlatformerEntity* target = nullptr;
		MinMaxPool* pocketPool = nullptr;
		std::function<void()> onPickPocket = nullptr;
		std::string saveKeyPickPocketed;

		RequestPickPocketArgs(PlatformerEntity* target, MinMaxPool* pocketPool, std::function<void()> onPickPocket, std::string saveKeyPickPocketed)
			: target(target), pocketPool(pocketPool), onPickPocket(onPickPocket), saveKeyPickPocketed(saveKeyPickPocketed)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerRequestPickPocket(RequestPickPocketArgs args);
};
