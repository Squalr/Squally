#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolUREquipment : public MinMaxPool
{
public:
	static ChestPoolUREquipment* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolUREquipment(cocos2d::ValueMap& properties);
	virtual ~ChestPoolUREquipment();

private:
	typedef MinMaxPool super;
};
