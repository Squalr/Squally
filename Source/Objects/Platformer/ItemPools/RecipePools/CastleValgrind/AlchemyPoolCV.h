#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolCV : public MinMaxPool
{
public:
	static AlchemyPoolCV* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolCV(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolCV();

private:
	typedef MinMaxPool super;
};
