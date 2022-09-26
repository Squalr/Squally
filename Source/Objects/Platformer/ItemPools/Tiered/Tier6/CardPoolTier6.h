#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier6 : public MinMaxPool
{
public:
	static CardPoolTier6* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	CardPoolTier6(SampleMethod sampleMethod, int min, int max);
	virtual ~CardPoolTier6();

private:
	typedef MinMaxPool super;
};
