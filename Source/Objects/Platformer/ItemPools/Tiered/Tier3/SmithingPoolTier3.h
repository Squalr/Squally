#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier3 : public MinMaxPool
{
public:
	static SmithingPoolTier3* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier3(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier3();

private:
	typedef MinMaxPool super;
};
