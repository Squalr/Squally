#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class ChestPoolEFAra : public MinMaxPool
{
public:
	static ChestPoolEFAra* create(cocos2d::ValueMap& properties);

	static const std::string PoolName;

protected:
	ChestPoolEFAra(cocos2d::ValueMap& properties);
	virtual ~ChestPoolEFAra();

private:
	typedef MinMaxPool super;
};
