#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolLCWeak : public DropPool
{
public:
	static DropPoolLCWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolLCWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolLCWeak();

private:
	typedef DropPool super;
};
