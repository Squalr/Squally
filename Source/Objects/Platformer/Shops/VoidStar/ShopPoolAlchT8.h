#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolAlchT8 : public ShopPool
{
public:
	static ShopPoolAlchT8* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolAlchT8(cocos2d::ValueMap& properties);
	virtual ~ShopPoolAlchT8();

private:
	typedef ShopPool super;
};
