#pragma once

#include "Engine/Inventory/DropPool.h"

class ErrorDropPool : public DropPool
{
public:
	static ErrorDropPool* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ErrorDropPool(cocos2d::ValueMap& properties);
	virtual ~ErrorDropPool();

private:
	typedef DropPool super;
};
