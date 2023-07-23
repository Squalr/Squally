#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolBPRare : public MinMaxPool
{
public:
	static ChestPoolBPRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolBPRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolBPRare();

private:
	typedef MinMaxPool super;
};
