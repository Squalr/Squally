#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolDHWeak : public DropPool
{
public:
	static DropPoolDHWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolDHWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolDHWeak();

private:
	typedef DropPool super;
};
