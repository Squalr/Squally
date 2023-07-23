#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolFFRare : public MinMaxPool
{
public:
	static ChestPoolFFRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolFFRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolFFRare();

private:
	typedef MinMaxPool super;
};
