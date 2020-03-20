#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolPinata : public MinMaxPool
{
public:
	static ChestPoolPinata* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolPinata(cocos2d::ValueMap& properties);
	virtual ~ChestPoolPinata();

private:
	typedef MinMaxPool super;
};
