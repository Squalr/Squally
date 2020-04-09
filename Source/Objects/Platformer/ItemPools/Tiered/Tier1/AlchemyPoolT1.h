#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolT1 : public MinMaxPool
{
public:
	static AlchemyPoolT1* create(SampleMethod sampleMethod = SampleMethod::Random, int min = 1, int max = 1);

protected:
	AlchemyPoolT1(SampleMethod sampleMethod, int min, int max);
	virtual ~AlchemyPoolT1();

private:
	typedef MinMaxPool super;
};
