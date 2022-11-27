#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDHGeneric : public MinMaxPool
{
public:
	static ChestPoolDHGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDHGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDHGeneric();

private:
	typedef MinMaxPool super;
};
