#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT7 : public ShopPool
{
public:
	static ShopPoolSmithT7* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT7(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT7();

private:
	typedef ShopPool super;
};
