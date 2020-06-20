#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier2 : public MinMaxPool
{
public:
	static AlchemyPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier2();

private:
	typedef MinMaxPool super;
};
