#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier8 : public MinMaxPool
{
public:
	static CardPoolTier8* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier8(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier8();

private:
	typedef MinMaxPool super;
};
