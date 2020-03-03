#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolRamWheel : public MinMaxPool
{
public:
	static ChestPoolRamWheel* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolRamWheel(cocos2d::ValueMap& properties);
	virtual ~ChestPoolRamWheel();

private:
	typedef MinMaxPool super;
};
