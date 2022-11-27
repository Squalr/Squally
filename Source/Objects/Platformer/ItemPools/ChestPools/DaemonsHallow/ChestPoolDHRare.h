#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDHRare : public MinMaxPool
{
public:
	static ChestPoolDHRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDHRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDHRare();

private:
	typedef MinMaxPool super;
};
