#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier5 : public MinMaxPool
{
public:
	static CardPoolTier5* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier5(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier5();

private:
	typedef MinMaxPool super;
};
