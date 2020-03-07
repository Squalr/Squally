#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFSpecial : public MinMaxPool
{
public:
	static ChestPoolEFSpecial* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFSpecial(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFSpecial();

private:
	typedef MinMaxPool super;
};
