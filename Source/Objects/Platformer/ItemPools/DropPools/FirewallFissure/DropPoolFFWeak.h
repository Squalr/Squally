#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolFFWeak : public DropPool
{
public:
	static DropPoolFFWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolFFWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolFFWeak();

private:
	typedef DropPool super;
};
