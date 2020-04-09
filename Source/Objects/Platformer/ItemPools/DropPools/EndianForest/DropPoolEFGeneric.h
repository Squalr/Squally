#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolEFGeneric : public DropPool
{
public:
	static DropPoolEFGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolEFGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolEFGeneric();

private:
	typedef DropPool super;
};
