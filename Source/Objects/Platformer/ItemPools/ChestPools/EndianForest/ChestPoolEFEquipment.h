#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFEquipment : public MinMaxPool
{
public:
	static ChestPoolEFEquipment* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFEquipment(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFEquipment();

private:
	typedef MinMaxPool super;
};
