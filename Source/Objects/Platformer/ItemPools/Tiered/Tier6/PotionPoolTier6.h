#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier6 : public MinMaxPool
{
public:
	static PotionPoolTier6* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier6(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier6();

private:
	typedef MinMaxPool super;
};
