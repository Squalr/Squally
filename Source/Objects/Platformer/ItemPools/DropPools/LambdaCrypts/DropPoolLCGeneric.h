#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolLCGeneric : public DropPool
{
public:
	static DropPoolLCGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolLCGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolLCGeneric();

private:
	typedef DropPool super;
};
