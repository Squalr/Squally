#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class WeaponPoolTier1 : public MinMaxPool
{
public:
	static WeaponPoolTier1* create(SampleMethod sampleMethod);

protected:
	WeaponPoolTier1(SampleMethod sampleMethod);
	~WeaponPoolTier1();

private:
	typedef MinMaxPool super;
};
