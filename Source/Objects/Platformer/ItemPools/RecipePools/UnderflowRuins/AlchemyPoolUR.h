#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolUR : public MinMaxPool
{
public:
	static AlchemyPoolUR* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolUR(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolUR();

private:
	typedef MinMaxPool super;
};
