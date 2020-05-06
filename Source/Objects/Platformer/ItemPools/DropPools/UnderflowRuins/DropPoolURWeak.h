#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolURWeak : public DropPool
{
public:
	static DropPoolURWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolURWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolURWeak();

private:
	typedef DropPool super;
};
