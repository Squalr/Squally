#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier4 : public MinMaxPool
{
public:
	static PotionPoolTier4* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier4(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier4();

private:
	typedef MinMaxPool super;
};
