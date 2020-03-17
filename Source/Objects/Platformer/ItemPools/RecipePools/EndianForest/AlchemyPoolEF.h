#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolEF : public MinMaxPool
{
public:
	static AlchemyPoolEF* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolEF(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolEF();

private:
	typedef MinMaxPool super;
};
