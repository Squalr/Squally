#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolCVWeak : public DropPool
{
public:
	static DropPoolCVWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolCVWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolCVWeak();

private:
	typedef DropPool super;
};
