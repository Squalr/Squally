#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class EquipmentPoolTier2 : public MinMaxPool
{
public:
	static EquipmentPoolTier2* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	EquipmentPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~EquipmentPoolTier2();

private:
	typedef MinMaxPool super;
};
