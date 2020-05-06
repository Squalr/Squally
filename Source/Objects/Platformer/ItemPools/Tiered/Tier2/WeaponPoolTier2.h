#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class WeaponPoolTier2 : public MinMaxPool
{
public:
	static WeaponPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	WeaponPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~WeaponPoolTier2();

private:
	typedef MinMaxPool super;
};
