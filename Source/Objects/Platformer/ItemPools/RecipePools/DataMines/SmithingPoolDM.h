#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolDM : public MinMaxPool
{
public:
	static SmithingPoolDM* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolDM(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolDM();

private:
	typedef MinMaxPool super;
};
