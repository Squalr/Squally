#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT8 : public ShopPool
{
public:
	static ShopPoolInnT8* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT8(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT8();

private:
	typedef ShopPool super;
};
