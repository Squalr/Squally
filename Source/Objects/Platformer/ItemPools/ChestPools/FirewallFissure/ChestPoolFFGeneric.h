#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolFFGeneric : public MinMaxPool
{
public:
	static ChestPoolFFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolFFGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolFFGeneric();

private:
	typedef MinMaxPool super;
};
