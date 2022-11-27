#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolCVGeneric : public DropPool
{
public:
	static DropPoolCVGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolCVGeneric(cocos2d::ValueMap& properties);
	virtual ~DropPoolCVGeneric();

private:
	typedef DropPool super;
};
