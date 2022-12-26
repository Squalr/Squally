#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT3 : public ShopPool
{
public:
	static ShopPoolSmithT3* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT3(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT3();

private:
	typedef ShopPool super;
};
