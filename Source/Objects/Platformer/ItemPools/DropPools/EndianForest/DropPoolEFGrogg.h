#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolEFGrogg : public DropPool
{
public:
	static DropPoolEFGrogg* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolEFGrogg(cocos2d::ValueMap& properties);
	virtual ~DropPoolEFGrogg();

private:
	typedef DropPool super;
};
