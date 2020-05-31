#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolURMirror : public MinMaxPool
{
public:
	static ChestPoolURMirror* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolURMirror(cocos2d::ValueMap& properties);
	virtual ~ChestPoolURMirror();

private:
	typedef MinMaxPool super;
};
