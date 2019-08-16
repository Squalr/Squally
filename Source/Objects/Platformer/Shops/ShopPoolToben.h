#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolToben : public ShopPool
{
public:
	static ShopPoolToben* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyShopPoolToben;
	static const std::string PoolName;

protected:
	ShopPoolToben(cocos2d::ValueMap& properties);
	~ShopPoolToben();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef ShopPool super;
};
