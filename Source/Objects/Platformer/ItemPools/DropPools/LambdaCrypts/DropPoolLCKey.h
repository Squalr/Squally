#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class DropPoolLCKey : public MinMaxPool
{
public:
	static DropPoolLCKey* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	DropPoolLCKey(SampleMethod sampleMethod, int min, int max);
	virtual ~DropPoolLCKey();

private:
	typedef MinMaxPool super;
};
