#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMDiamond : public MinMaxPool
{
public:
	static ChestPoolDMDiamond* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMDiamond(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMDiamond();

private:
	typedef MinMaxPool super;
};
