#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier8 : public MinMaxPool
{
public:
	static AlchemyPoolTier8* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier8(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier8();

private:
	typedef MinMaxPool super;
};
