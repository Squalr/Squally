#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolUROsiris : public DropPool
{
public:
	static DropPoolUROsiris* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolUROsiris(cocos2d::ValueMap& properties);
	virtual ~DropPoolUROsiris();

private:
	typedef DropPool super;
};
