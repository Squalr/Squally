#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolDemonHeart : public MinMaxPool
{
public:
	static SmithingPoolDemonHeart* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolDemonHeart(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolDemonHeart();

private:
	typedef MinMaxPool super;
};
