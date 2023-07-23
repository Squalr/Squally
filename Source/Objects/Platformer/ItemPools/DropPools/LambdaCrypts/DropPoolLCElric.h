#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolLCElric : public DropPool
{
public:
	static DropPoolLCElric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolLCElric(cocos2d::ValueMap& properties);
	virtual ~DropPoolLCElric();

private:
	typedef DropPool super;
};
