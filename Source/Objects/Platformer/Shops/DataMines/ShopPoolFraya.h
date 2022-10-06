#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolFraya : public ShopPool
{
public:
	static ShopPoolFraya* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolFraya(cocos2d::ValueMap& properties);
	virtual ~ShopPoolFraya();

private:
	typedef ShopPool super;
};
