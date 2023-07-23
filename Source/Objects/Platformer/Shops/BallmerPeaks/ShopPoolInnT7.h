#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT7 : public ShopPool
{
public:
	static ShopPoolInnT7* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT7(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT7();

private:
	typedef ShopPool super;
};
