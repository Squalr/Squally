#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolLCLazarus : public DropPool
{
public:
	static DropPoolLCLazarus* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolLCLazarus(cocos2d::ValueMap& properties);
	virtual ~DropPoolLCLazarus();

private:
	typedef DropPool super;
};
