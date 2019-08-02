#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolToben : public ShopPool
{
public:
	static ShopPoolToben* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyShopPoolToben;
	static const std::string PoolName;

protected:
	ShopPoolToben(cocos2d::ValueMap& initProperties);
	~ShopPoolToben();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef ShopPool super;
};
