#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier7 : public MinMaxPool
{
public:
	static CraftingPoolTier7* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier7(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier7();

private:
	typedef MinMaxPool super;
};
