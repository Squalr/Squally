#pragma once
#include <functional>
#include <string>

class InteractObject;
class PlatformerEntity;
class MinMaxPool;

class HelperEvents
{
public:
	static const std::string EventFindScrappy;
	static const std::string EventRequestPickPocket;
	static const std::string EventRequestRepair;
	static const std::string EventRequestSoulHarvest;

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
		InteractObject* target = nullptr;
		std::function<void()> onRepaired = nullptr;
		std::string repairEvent;
		std::string saveKeyRepaired;

		RequestRepairArgs(InteractObject* target, std::function<void()> onRepaired, std::string repairEvent, std::string saveKeyRepaired)
			: target(target), onRepaired(onRepaired), repairEvent(repairEvent), saveKeyRepaired(saveKeyRepaired)
		{
		}
	};

	struct RequestSoulHarvestArgs
	{
		PlatformerEntity* target = nullptr;
		std::function<void()> onSoulHarvested = nullptr;
		std::string saveKeySoulHarvested;

		RequestSoulHarvestArgs(PlatformerEntity* target, std::function<void()> onSoulHarvested, std::string saveKeySoulHarvested)
			: target(target), onSoulHarvested(onSoulHarvested), saveKeySoulHarvested(saveKeySoulHarvested)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerRequestPickPocket(RequestPickPocketArgs args);
	static void TriggerRequestRepair(RequestRepairArgs args);
	static void TriggerRequestSoulHarvest(RequestSoulHarvestArgs args);
};
