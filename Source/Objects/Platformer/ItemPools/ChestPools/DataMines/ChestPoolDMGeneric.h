#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMGeneric : public MinMaxPool
{
public:
	static ChestPoolDMGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMGeneric();

private:
	typedef MinMaxPool super;
};
