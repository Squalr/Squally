#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class AlchemyPoolDM : public MinMaxPool
{
public:
	static AlchemyPoolDM* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	AlchemyPoolDM(cocos2d::ValueMap& properties);
	virtual ~AlchemyPoolDM();

private:
	typedef MinMaxPool super;
};
