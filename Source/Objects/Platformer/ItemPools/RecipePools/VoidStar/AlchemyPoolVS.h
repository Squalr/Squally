#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolVS : public MinMaxPool
{
public:
	static AlchemyPoolVS* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolVS(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolVS();

private:
	typedef MinMaxPool super;
};
