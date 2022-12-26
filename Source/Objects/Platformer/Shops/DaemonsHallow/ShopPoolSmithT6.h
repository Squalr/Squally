#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT6 : public ShopPool
{
public:
	static ShopPoolSmithT6* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT6(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT6();

private:
	typedef ShopPool super;
};
