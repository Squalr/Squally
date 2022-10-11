#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier7 : public MinMaxPool
{
public:
	static AlchemyPoolTier7* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier7(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier7();

private:
	typedef MinMaxPool super;
};
