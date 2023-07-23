#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT1 : public ShopPool
{
public:
	static ShopPoolSmithT1* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT1(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT1();

private:
	typedef ShopPool super;
};
