#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolLCGeneric : public MinMaxPool
{
public:
	static ChestPoolLCGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolLCGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolLCGeneric();

private:
	typedef MinMaxPool super;
};
