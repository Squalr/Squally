#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT5 : public ShopPool
{
public:
	static ShopPoolSmithT5* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT5(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT5();

private:
	typedef ShopPool super;
};
