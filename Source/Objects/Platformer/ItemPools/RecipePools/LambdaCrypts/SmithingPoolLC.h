#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolLC : public MinMaxPool
{
public:
	static SmithingPoolLC* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolLC(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolLC();

private:
	typedef MinMaxPool super;
};
