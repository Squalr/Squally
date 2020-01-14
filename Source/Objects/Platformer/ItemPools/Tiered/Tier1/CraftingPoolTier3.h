#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier3 : public MinMaxPool
{
public:
	static CraftingPoolTier3* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier3(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier3();

private:
	typedef MinMaxPool super;
};
