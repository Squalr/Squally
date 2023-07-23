#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolVSWeak : public DropPool
{
public:
	static DropPoolVSWeak* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolVSWeak(cocos2d::ValueMap& properties);
	virtual ~DropPoolVSWeak();

private:
	typedef DropPool super;
};
