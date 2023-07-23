#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT3 : public ShopPool
{
public:
	static ShopPoolAlchT3* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT3(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT3();

private:
	typedef ShopPool super;
};
