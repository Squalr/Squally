#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolDMWeak : public DropPool
{
public:
	static DropPoolDMWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolDMWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolDMWeak();

private:
	typedef DropPool super;
};
