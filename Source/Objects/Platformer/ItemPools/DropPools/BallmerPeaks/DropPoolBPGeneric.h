#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolBPGeneric : public DropPool
{
public:
	static DropPoolBPGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolBPGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolBPGeneric();

private:
	typedef DropPool super;
};
