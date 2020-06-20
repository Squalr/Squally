#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolDH : public MinMaxPool
{
public:
	static AlchemyPoolDH* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolDH(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolDH();

private:
	typedef MinMaxPool super;
};
