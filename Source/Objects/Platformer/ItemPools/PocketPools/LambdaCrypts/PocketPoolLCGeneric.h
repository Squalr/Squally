#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolLCGeneric : public MinMaxPool
{
public:
	static PocketPoolLCGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolLCGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolLCGeneric();

private:
	typedef MinMaxPool super;
};
