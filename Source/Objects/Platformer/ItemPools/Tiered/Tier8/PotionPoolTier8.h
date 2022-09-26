#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier8 : public MinMaxPool
{
public:
	static PotionPoolTier8* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier8(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier8();

private:
	typedef MinMaxPool super;
};
