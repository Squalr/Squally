#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolVS : public MinMaxPool
{
public:
	static SmithingPoolVS* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolVS(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolVS();

private:
	typedef MinMaxPool super;
};
