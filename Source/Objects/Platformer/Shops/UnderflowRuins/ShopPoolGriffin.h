#pragma once

#include "Objects/Platformer/Shops/ShopPool.h"

class ShopPoolGriffin : public ShopPool
{
public:
	static ShopPoolGriffin* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PoolName;

protected:
	ShopPoolGriffin(cocos2d::ValueMap& properties);
	virtual ~ShopPoolGriffin();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef ShopPool super;
};
