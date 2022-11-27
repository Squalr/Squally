#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolVSGeneric : public MinMaxPool
{
public:
	static ChestPoolVSGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolVSGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolVSGeneric();

private:
	typedef MinMaxPool super;
};
