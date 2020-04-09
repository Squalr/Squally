#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier1 : public MinMaxPool
{
public:
	static CardPoolTier1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier1(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier1();

private:
	typedef MinMaxPool super;
};
