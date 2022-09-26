#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier6 : public MinMaxPool
{
public:
	static AlchemyPoolTier6* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier6(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier6();

private:
	typedef MinMaxPool super;
};
