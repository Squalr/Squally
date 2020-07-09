#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier3 : public MinMaxPool
{
public:
	static CardPoolTier3* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier3(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier3();

private:
	typedef MinMaxPool super;
};
