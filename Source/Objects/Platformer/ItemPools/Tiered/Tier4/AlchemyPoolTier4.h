#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier4 : public MinMaxPool
{
public:
	static AlchemyPoolTier4* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier4(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier4();

private:
	typedef MinMaxPool super;
};
