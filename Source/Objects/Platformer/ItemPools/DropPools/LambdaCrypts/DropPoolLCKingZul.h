#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolLCKingZul : public DropPool
{
public:
	static DropPoolLCKingZul* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolLCKingZul(cocos2d::ValueMap& properties);
	virtual ~DropPoolLCKingZul();

private:
	typedef DropPool super;
};
