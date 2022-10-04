#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolShen : public ShopPool
{
public:
	static ShopPoolShen* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolShen(cocos2d::ValueMap& properties);
	virtual ~ShopPoolShen();

private:
	typedef ShopPool super;
};
