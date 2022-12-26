#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT1 : public ShopPool
{
public:
	static ShopPoolAlchT1* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT1(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT1();

private:
	typedef ShopPool super;
};
