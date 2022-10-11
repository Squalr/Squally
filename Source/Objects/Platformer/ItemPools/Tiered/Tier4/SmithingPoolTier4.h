#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier4 : public MinMaxPool
{
public:
	static SmithingPoolTier4* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier4(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier4();

private:
	typedef MinMaxPool super;
};
