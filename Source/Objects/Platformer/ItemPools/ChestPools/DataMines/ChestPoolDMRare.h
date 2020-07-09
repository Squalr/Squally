#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMRare : public MinMaxPool
{
public:
	static ChestPoolDMRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMRare();

private:
	typedef MinMaxPool super;
};
