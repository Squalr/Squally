#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolBP : public MinMaxPool
{
public:
	static AlchemyPoolBP* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolBP(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolBP();

private:
	typedef MinMaxPool super;
};
