#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolSpecialAra : public MinMaxPool
{
public:
	static ChestPoolSpecialAra* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolSpecialAra(cocos2d::ValueMap& properties);
	virtual ~ChestPoolSpecialAra();

private:
	typedef MinMaxPool super;
};
