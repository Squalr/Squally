#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolSmithT8 : public ShopPool
{
public:
	static ShopPoolSmithT8* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolSmithT8(cocos2d::ValueMap& properties);
	virtual ~ShopPoolSmithT8();

private:
	typedef ShopPool super;
};
