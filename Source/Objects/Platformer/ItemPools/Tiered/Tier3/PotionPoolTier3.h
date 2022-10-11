#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier3 : public MinMaxPool
{
public:
	static PotionPoolTier3* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier3(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier3();

private:
	typedef MinMaxPool super;
};
