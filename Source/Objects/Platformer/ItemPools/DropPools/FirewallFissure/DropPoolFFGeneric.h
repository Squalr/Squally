#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolFFGeneric : public DropPool
{
public:
	static DropPoolFFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolFFGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolFFGeneric();

private:
	typedef DropPool super;
};
