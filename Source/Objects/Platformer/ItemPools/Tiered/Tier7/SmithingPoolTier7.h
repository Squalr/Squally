#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier7 : public MinMaxPool
{
public:
	static SmithingPoolTier7* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier7(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier7();

private:
	typedef MinMaxPool super;
};
