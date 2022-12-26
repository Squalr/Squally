#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT2 : public ShopPool
{
public:
	static ShopPoolInnT2* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT2(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT2();

private:
	typedef ShopPool super;
};
