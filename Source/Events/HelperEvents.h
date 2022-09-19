#pragma once
#include <functional>
#include <string>

class GameObject;
class PlatformerEntity;
class MinMaxPool;

class HelperEvents
{
public:
	static const std::string EventFindScrappy;
	static const std::string EventRequestPickPocket;
	static const std::string EventRequestRepair;

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

	struct RequestRepairArgs
	{
		GameObject* target = nullptr;
		std::string repairEvent;
		std::string saveKeyRepaired;

		RequestRepairArgs(GameObject* target, std::string repairEvent, std::string saveKeyRepaired)
			: target(target), repairEvent(repairEvent), saveKeyRepaired(saveKeyRepaired)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerRequestPickPocket(RequestPickPocketArgs args);
	static void TriggerRequestRepair(RequestRepairArgs args);
};
