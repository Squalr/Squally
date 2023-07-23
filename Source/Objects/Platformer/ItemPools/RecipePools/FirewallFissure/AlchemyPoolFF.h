#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolFF : public MinMaxPool
{
public:
	static AlchemyPoolFF* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolFF(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolFF();

private:
	typedef MinMaxPool super;
};
