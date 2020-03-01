#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFGeneric : public MinMaxPool
{
public:
	static ChestPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFGeneric();

private:
	typedef MinMaxPool super;
};
