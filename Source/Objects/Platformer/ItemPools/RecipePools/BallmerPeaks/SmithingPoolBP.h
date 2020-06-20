#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolBP : public MinMaxPool
{
public:
	static SmithingPoolBP* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolBP(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolBP();

private:
	typedef MinMaxPool super;
};
