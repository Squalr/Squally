#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier6 : public MinMaxPool
{
public:
	static SmithingPoolTier6* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier6(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier6();

private:
	typedef MinMaxPool super;
};
