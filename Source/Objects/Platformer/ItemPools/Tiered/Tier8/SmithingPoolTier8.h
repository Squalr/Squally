#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier8 : public MinMaxPool
{
public:
	static SmithingPoolTier8* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier8(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier8();

private:
	typedef MinMaxPool super;
};
