#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolTier2 : public MinMaxPool
{
public:
	static SmithingPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	SmithingPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolTier2();

private:
	typedef MinMaxPool super;
};
