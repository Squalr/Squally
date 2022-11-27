#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolVSRare : public MinMaxPool
{
public:
	static ChestPoolVSRare* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolVSRare(cocos2d::ValueMap& properties);
	virtual ~ChestPoolVSRare();

private:
	typedef MinMaxPool super;
};
