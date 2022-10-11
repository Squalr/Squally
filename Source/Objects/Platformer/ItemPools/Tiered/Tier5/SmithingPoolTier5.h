#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier5 : public MinMaxPool
{
public:
	static SmithingPoolTier5* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier5(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier5();

private:
	typedef MinMaxPool super;
};
