#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolEFWeak : public DropPool
{
public:
	static DropPoolEFWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolEFWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolEFWeak();

private:
	typedef DropPool super;
};
