#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PotionPoolTier2 : public MinMaxPool
{
public:
	static PotionPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	PotionPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~PotionPoolTier2();

private:
	typedef MinMaxPool super;
};
