#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT4 : public ShopPool
{
public:
	static ShopPoolSmithT4* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT4(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT4();

private:
	typedef ShopPool super;
};
