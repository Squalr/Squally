#pragma once

#include "Engine/Inventory/MinMaxPool.h"

// Merge pools will combine all nested pools into a single pool. This is useful for better sampling, as sampling occurs once instead of for each pool.
class MergePool : public MinMaxPool
{
public:
	static MergePool* create(SampleMethod sampleMethod, int min = 1, int max = 1, std::vector<MinMaxPool*> mergedPools = { }, std::vector<MinMaxPool*> nestedPools = { });

protected:
	MergePool(const cocos2d::ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, std::vector<MinMaxPool*> mergedPools, std::vector<MinMaxPool*> nestedPools);
	virtual ~MergePool();

private:
	typedef MinMaxPool super;
};
