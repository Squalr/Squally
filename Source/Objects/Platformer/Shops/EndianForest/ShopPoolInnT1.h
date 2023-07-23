#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT1 : public ShopPool
{
public:
	static ShopPoolInnT1* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT1(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT1();

private:
	typedef ShopPool super;
};
