#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT4 : public ShopPool
{
public:
	static ShopPoolInnT4* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT4(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT4();

private:
	typedef ShopPool super;
};
