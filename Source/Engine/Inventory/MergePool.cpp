#include "MergePool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"
#include "Engine/Inventory/ItemChance.h"

using namespace cocos2d;

MergePool* MergePool::create(SampleMethod sampleMethod, int min, int max, std::vector<MinMaxPool*> mergedPools, std::vector<MinMaxPool*> nestedPools)
{
	ValueMap properties = ValueMap();
	MergePool* instance = new MergePool(properties, "", sampleMethod, min, max, mergedPools, nestedPools);

	instance->autorelease();

	return instance;
}

MergePool::MergePool(const ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, std::vector<MinMaxPool*> mergedPools, std::vector<MinMaxPool*> nestedPools)
	: super(properties, poolName, sampleMethod, minItems, maxItems, nestedPools)
{
	// Nested pools are not passed through to the MinMax pool. Instead, we steal all of the items and merge them into this pool (hence a merge pool)
	for (auto pool : mergedPools)
	{
		for (auto itemChance : pool->itemPool)
		{
			this->addItemToPool(itemChance->clone());
		}
	}
}

MergePool::~MergePool()
{
}
