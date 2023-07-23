#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolVSGeneric : public DropPool
{
public:
	static DropPoolVSGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolVSGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolVSGeneric();

private:
	typedef DropPool super;
};
