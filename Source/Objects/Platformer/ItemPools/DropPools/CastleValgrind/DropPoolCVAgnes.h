#pragma once

#include "Engine/Inventory/DropPool.h"

class DropPoolCVAgnes : public DropPool
{
public:
	static DropPoolCVAgnes* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	DropPoolCVAgnes(cocos2d::ValueMap& properties);
	virtual ~DropPoolCVAgnes();

private:
	typedef DropPool super;
};
