#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFRare : public MinMaxPool
{
public:
	static ChestPoolEFRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFRare();

private:
	typedef MinMaxPool super;
};
