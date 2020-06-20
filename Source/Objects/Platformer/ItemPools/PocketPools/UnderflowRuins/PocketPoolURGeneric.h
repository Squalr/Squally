#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolURGeneric : public MinMaxPool
{
public:
	static PocketPoolURGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolURGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolURGeneric();

private:
	typedef MinMaxPool super;
};
