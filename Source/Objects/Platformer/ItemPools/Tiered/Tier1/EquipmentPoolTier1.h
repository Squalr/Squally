#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class EquipmentPoolTier1 : public MinMaxPool
{
public:
	static EquipmentPoolTier1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	EquipmentPoolTier1(SampleMethod sampleMethod, int min, int max);
	virtual ~EquipmentPoolTier1();

private:
	typedef MinMaxPool super;
};
