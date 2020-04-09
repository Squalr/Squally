#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier4 : public MinMaxPool
{
public:
	static CraftingPoolTier4* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier4(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier4();

private:
	typedef MinMaxPool super;
};
