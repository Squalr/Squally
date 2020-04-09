#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFWeapon : public MinMaxPool
{
public:
	static ChestPoolEFWeapon* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFWeapon(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFWeapon();

private:
	typedef MinMaxPool super;
};
