#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolBPWeak : public DropPool
{
public:
	static DropPoolBPWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolBPWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolBPWeak();

private:
	typedef DropPool super;
};
