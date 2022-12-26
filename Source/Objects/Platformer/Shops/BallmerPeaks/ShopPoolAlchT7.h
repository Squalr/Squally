#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT7 : public ShopPool
{
public:
	static ShopPoolAlchT7* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT7(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT7();

private:
	typedef ShopPool super;
};
