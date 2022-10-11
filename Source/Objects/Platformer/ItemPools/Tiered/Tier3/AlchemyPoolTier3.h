#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier3 : public MinMaxPool
{
public:
	static AlchemyPoolTier3* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier3(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier3();

private:
	typedef MinMaxPool super;
};
