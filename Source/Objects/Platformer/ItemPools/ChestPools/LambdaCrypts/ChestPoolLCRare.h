#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolLCRare : public MinMaxPool
{
public:
	static ChestPoolLCRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolLCRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolLCRare();

private:
	typedef MinMaxPool super;
};
