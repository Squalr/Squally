#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier1 : public MinMaxPool
{
public:
	static CraftingPoolTier1* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier1(SampleMethod sampleMethod, int min, int max);
	~CraftingPoolTier1();

private:
	typedef MinMaxPool super;
};
