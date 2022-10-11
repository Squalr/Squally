#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAres : public ShopPool
{
public:
	static ShopPoolAres* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAres(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAres();

private:
	typedef ShopPool super;
};
