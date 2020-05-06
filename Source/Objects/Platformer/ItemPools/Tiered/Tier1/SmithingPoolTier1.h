#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier1 : public MinMaxPool
{
public:
	static SmithingPoolTier1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier1(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier1();

private:
	typedef MinMaxPool super;
};
