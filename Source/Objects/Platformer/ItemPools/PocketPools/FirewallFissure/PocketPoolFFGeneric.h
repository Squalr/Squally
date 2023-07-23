#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolFFGeneric : public MinMaxPool
{
public:
	static PocketPoolFFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolFFGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolFFGeneric();

private:
	typedef MinMaxPool super;
};
