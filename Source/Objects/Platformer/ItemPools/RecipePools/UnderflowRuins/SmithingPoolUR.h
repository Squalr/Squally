#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolUR : public MinMaxPool
{
public:
	static SmithingPoolUR* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolUR(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolUR();

private:
	typedef MinMaxPool super;
};
