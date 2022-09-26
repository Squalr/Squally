#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier7 : public MinMaxPool
{
public:
	static CardPoolTier7* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier7(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier7();

private:
	typedef MinMaxPool super;
};
