#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolCVRare : public MinMaxPool
{
public:
	static ChestPoolCVRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolCVRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolCVRare();

private:
	typedef MinMaxPool super;
};
