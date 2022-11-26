#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolCVGeneric : public MinMaxPool
{
public:
	static ChestPoolCVGeneric* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolCVGeneric(cocos2d::ValueMap& properties);
	virtual ~ChestPoolCVGeneric();

private:
	typedef MinMaxPool super;
};
