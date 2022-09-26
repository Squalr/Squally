#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier5 : public MinMaxPool
{
public:
	static PotionPoolTier5* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier5(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier5();

private:
	typedef MinMaxPool super;
};
