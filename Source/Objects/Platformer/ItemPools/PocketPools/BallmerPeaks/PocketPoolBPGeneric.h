#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolBPGeneric : public MinMaxPool
{
public:
	static PocketPoolBPGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolBPGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolBPGeneric();

private:
	typedef MinMaxPool super;
};
