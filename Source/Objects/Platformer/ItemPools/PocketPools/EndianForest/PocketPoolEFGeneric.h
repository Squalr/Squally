#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class PocketPoolEFGeneric : public MinMaxPool
{
public:
	static PocketPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	PocketPoolEFGeneric(cocos2d::ValueMap& properties);
	~PocketPoolEFGeneric();

private:
	typedef MinMaxPool super;
};
