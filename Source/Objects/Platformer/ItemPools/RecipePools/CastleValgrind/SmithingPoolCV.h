#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class SmithingPoolCV : public MinMaxPool
{
public:
	static SmithingPoolCV* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	SmithingPoolCV(cocos2d::ValueMap& properties);
	virtual ~SmithingPoolCV();

private:
	typedef MinMaxPool super;
};
