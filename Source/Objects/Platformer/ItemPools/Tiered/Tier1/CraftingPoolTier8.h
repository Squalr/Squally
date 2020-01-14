#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier8 : public MinMaxPool
{
public:
	static CraftingPoolTier8* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier8(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier8();

private:
	typedef MinMaxPool super;
};
