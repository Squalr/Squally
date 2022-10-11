#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolTier5 : public MinMaxPool
{
public:
	static AlchemyPoolTier5* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolTier5(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolTier5();

private:
	typedef MinMaxPool super;
};
