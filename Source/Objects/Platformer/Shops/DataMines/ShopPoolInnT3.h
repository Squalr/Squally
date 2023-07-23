#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolInnT3 : public ShopPool
{
public:
	static ShopPoolInnT3* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolInnT3(cocos2d::ValueMap& properties);
	virtual ~ShopPoolInnT3();

private:
	typedef ShopPool super;
};
