#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT5 : public ShopPool
{
public:
	static ShopPoolInnT5* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT5(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT5();

private:
	typedef ShopPool super;
};
