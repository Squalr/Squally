#pragma once

#include "Engine/Maps/GameObject.h"

class ClickableNode;
class ItemPreview;
class Item;

class ShopItem : public GameObject
{
public:
	static ShopItem* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyShopItem;
	static const std::string MapKeyPropertyShopPool;

protected:
	ShopItem(cocos2d::ValueMap& initProperties);
	~ShopItem();
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	ItemPreview* itemPreview;
	Item* item;
	cocos2d::Node* itemNode;
	ClickableNode* itemClickHitbox;
	std::string poolName;
};
