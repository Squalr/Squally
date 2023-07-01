#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolVSGeneric : public MinMaxPool
{
public:
	static PocketPoolVSGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolVSGeneric(cocos2d::ValueMap& properties);
	virtual ~PocketPoolVSGeneric();

private:
	typedef MinMaxPool super;
};
