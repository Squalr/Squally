#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolURGeneric : public MinMaxPool
{
public:
	static ChestPoolURGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolURGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolURGeneric();

private:
	typedef MinMaxPool super;
};
