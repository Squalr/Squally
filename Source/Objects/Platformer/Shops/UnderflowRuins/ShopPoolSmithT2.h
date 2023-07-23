#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT2 : public ShopPool
{
public:
	static ShopPoolSmithT2* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT2(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT2();

private:
	typedef ShopPool super;
};
