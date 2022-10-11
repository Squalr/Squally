#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFDungeonMap : public MinMaxPool
{
public:
	static ChestPoolEFDungeonMap* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFDungeonMap(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFDungeonMap();

private:
	typedef MinMaxPool super;
};
