#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier1 : public MinMaxPool
{
public:
	static AlchemyPoolTier1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier1(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier1();

private:
	typedef MinMaxPool super;
};
