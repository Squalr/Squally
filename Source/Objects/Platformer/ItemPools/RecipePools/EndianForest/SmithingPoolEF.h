#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolEF : public MinMaxPool
{
public:
	static SmithingPoolEF* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolEF(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolEF();

private:
	typedef MinMaxPool super;
};
