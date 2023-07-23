#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolBPGeneric : public MinMaxPool
{
public:
	static ChestPoolBPGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolBPGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolBPGeneric();

private:
	typedef MinMaxPool super;
};
