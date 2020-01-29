#pragma once

#include "Engine/Inventory/DropPool.h"

class EmptyDropPool : public DropPool
{
public:
	static EmptyDropPool* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	EmptyDropPool(cocos2d::ValueMap& properties);
	virtual ~EmptyDropPool();

private:
	typedef DropPool super;
};
