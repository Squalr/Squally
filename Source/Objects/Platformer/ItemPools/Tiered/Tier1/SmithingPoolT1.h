#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolT1 : public MinMaxPool
{
public:
	static SmithingPoolT1* create(SampleMethod sampleMethod, int min = 1, int max = 1);

protected:
	SmithingPoolT1(SampleMethod sampleMethod, int min, int max);
	virtual ~SmithingPoolT1();

private:
	typedef MinMaxPool super;
};
