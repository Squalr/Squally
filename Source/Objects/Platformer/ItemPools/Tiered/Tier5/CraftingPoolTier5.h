#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CraftingPoolTier5 : public MinMaxPool
{
public:
	static CraftingPoolTier5* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	CraftingPoolTier5(SampleMethod sampleMethod, int min, int max);
	virtual ~CraftingPoolTier5();

private:
	typedef MinMaxPool super;
};
