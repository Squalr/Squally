#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolHellCrystal : public MinMaxPool
{
public:
	static SmithingPoolHellCrystal* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolHellCrystal(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolHellCrystal();

private:
	typedef MinMaxPool super;
};
