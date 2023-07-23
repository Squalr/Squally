#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolFF : public MinMaxPool
{
public:
	static SmithingPoolFF* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolFF(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolFF();

private:
	typedef MinMaxPool super;
};
