#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolPurpleGem : public MinMaxPool
{
public:
	static ChestPoolPurpleGem* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolPurpleGem(cocos2d::ValueMap& properties);
	virtual ~ChestPoolPurpleGem();

private:
	typedef MinMaxPool super;
};
