#pragma once

#include <string>
#include <vector>

class Collectables
{
public:
	struct CollectableData
	{
		std::string unlockedResource;
		std::string lockedResource;
		std::string saveKey;

		CollectableData(std::string unlockedResource, std::string lockedResource, std::string saveKey)
		: unlockedResource(unlockedResource), lockedResource(lockedResource), saveKey(saveKey) { }
	};

	static int getCollectedAnimalTotal();
	static int getCollectedAnimalCount();
	static std::vector<CollectableData> getCollectableAnimalData();

private:
	static void buildAnimalData();

	static std::vector<Collectables::CollectableData> CollectableAnimalData;
};
