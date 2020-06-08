#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolDH : public MinMaxPool
{
public:
	static SmithingPoolDH* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolDH(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolDH();

private:
	typedef MinMaxPool super;
};
