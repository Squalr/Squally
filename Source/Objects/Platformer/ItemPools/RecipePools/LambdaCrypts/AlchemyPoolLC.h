#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolLC : public MinMaxPool
{
public:
	static AlchemyPoolLC* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolLC(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolLC();

private:
	typedef MinMaxPool super;
};
