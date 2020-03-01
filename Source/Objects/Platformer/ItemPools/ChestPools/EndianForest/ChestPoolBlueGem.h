#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolBlueGem : public MinMaxPool
{
public:
	static ChestPoolBlueGem* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolBlueGem(cocos2d::ValueMap& properties);
	virtual ~ChestPoolBlueGem();

private:
	typedef MinMaxPool super;
};
