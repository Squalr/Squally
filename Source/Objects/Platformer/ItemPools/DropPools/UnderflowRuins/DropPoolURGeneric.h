#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolURGeneric : public DropPool
{
public:
	static DropPoolURGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolURGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolURGeneric();

private:
	typedef DropPool super;
};
