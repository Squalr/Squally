#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolDHGeneric : public DropPool
{
public:
	static DropPoolDHGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolDHGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolDHGeneric();

private:
	typedef DropPool super;
};
