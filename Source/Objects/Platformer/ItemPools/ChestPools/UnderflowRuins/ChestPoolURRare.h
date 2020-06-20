#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolURRare : public MinMaxPool
{
public:
	static ChestPoolURRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolURRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolURRare();

private:
	typedef MinMaxPool super;
};
