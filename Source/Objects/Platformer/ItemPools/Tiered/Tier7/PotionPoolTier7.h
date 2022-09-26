#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier7 : public MinMaxPool
{
public:
	static PotionPoolTier7* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier7(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier7();

private:
	typedef MinMaxPool super;
};
