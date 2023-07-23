#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT6 : public ShopPool
{
public:
	static ShopPoolAlchT6* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT6(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT6();

private:
	typedef ShopPool super;
};
