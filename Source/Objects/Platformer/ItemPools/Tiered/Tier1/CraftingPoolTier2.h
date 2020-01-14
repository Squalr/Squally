#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier2 : public MinMaxPool
{
public:
	static CraftingPoolTier2* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier2(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier2();

private:
	typedef MinMaxPool super;
};
