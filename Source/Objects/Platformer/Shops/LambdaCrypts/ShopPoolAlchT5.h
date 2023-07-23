#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT5 : public ShopPool
{
public:
	static ShopPoolAlchT5* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT5(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT5();

private:
	typedef ShopPool super;
};
