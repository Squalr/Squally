#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMGold : public MinMaxPool
{
public:
	static ChestPoolDMGold* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMGold(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMGold();

private:
	typedef MinMaxPool super;
};
