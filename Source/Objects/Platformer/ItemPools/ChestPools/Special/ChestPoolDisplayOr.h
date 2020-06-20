#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDisplayOr : public MinMaxPool
{
public:
	static ChestPoolDisplayOr* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDisplayOr(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDisplayOr();

private:
	typedef MinMaxPool super;
};
