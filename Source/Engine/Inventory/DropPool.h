#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CurrencyPool;

// Drop pools combine a MinMaxPool with a CurrencyPool
class DropPool : public MinMaxPool
{
public:
	CurrencyPool* getCurrencyPool();

protected:
	DropPool(const cocos2d::ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, CurrencyPool* currencyPool, std::vector<MinMaxPool*> nestedPools = { });
	virtual ~DropPool();

private:
	typedef MinMaxPool super;

	CurrencyPool* currencyPool;
};
