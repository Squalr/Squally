#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT2 : public ShopPool
{
public:
	static ShopPoolAlchT2* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT2(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT2();

private:
	typedef ShopPool super;
};
