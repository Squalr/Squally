#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolPolyphemus : public ShopPool
{
public:
	static ShopPoolPolyphemus* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolPolyphemus(cocos2d::ValueMap& properties);
	virtual ~ShopPoolPolyphemus();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef ShopPool super;
};
