#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier6 : public MinMaxPool
{
public:
	static CraftingPoolTier6* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier6(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier6();

private:
	typedef MinMaxPool super;
};
