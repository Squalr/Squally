#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolDMCoal : public MinMaxPool
{
public:
	static ChestPoolDMCoal* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolDMCoal(cocos2d::ValueMap& properties);
	virtual ~ChestPoolDMCoal();

private:
	typedef MinMaxPool super;
};
