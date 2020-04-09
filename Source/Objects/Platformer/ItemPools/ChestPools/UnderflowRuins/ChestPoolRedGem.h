#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolRedGem : public MinMaxPool
{
public:
	static ChestPoolRedGem* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolRedGem(cocos2d::ValueMap& properties);
	virtual ~ChestPoolRedGem();

private:
	typedef MinMaxPool super;
};
