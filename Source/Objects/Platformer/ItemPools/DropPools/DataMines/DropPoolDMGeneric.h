#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolDMGeneric : public DropPool
{
public:
	static DropPoolDMGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolDMGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolDMGeneric();

private:
	typedef DropPool super;
};
