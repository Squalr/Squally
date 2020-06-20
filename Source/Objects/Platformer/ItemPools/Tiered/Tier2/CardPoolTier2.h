#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier2 : public MinMaxPool
{
public:
	static CardPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier2();

private:
	typedef MinMaxPool super;
};
