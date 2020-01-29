#include "DropPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyPool.h"

using namespace cocos2d;

DropPool::DropPool(ValueMap& properties, std::string poolName, SampleMethod sampleMethod, int minItems, int maxItems, CurrencyPool* currencyPool, std::vector<MinMaxPool*> nestedPools)
	: super(properties, poolName, sampleMethod, minItems, maxItems, nestedPools)
{
	this->currencyPool = currencyPool;

	if (this->currencyPool != nullptr)
	{
		this->addChild(this->currencyPool);
	}
}

DropPool::~DropPool()
{
}

CurrencyPool* DropPool::getCurrencyPool()
{
	return this->currencyPool;
}
