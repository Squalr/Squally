#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolEFGorgon : public DropPool
{
public:
	static DropPoolEFGorgon* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolEFGorgon(cocos2d::ValueMap& properties);
	virtual ~DropPoolEFGorgon();

private:
	typedef DropPool super;
};
