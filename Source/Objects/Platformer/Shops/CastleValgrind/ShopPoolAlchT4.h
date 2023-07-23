#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT4 : public ShopPool
{
public:
	static ShopPoolAlchT4* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT4(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT4();

private:
	typedef ShopPool super;
};
