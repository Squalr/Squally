#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolBrock : public ShopPool
{
public:
	static ShopPoolBrock* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolBrock(cocos2d::ValueMap& properties);
	virtual ~ShopPoolBrock();

private:
	typedef ShopPool super;
};
