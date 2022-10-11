#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier4 : public MinMaxPool
{
public:
	static CardPoolTier4* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier4(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier4();

private:
	typedef MinMaxPool super;
};
