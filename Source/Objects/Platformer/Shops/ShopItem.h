#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ConstantString;
class LocalizedLabel;
class ItemPreview;
class Item;

class ShopItem : public GameObject
{
public:
	static ShopItem* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;
	static const std::string PropertyShopPool;

protected:
	ShopItem(cocos2d::ValueMap& properties);
	virtual ~ShopItem();
	
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void sellItem();

	ItemPreview* itemPreview;
	Item* item;
	cocos2d::Node* itemNode;
	ClickableNode* itemClickHitbox;
	std::string poolName;
	cocos2d::Sprite* currencySprite;
	LocalizedLabel* itemCostLabel;
	ConstantString* itemCostString;

	int itemCost;
	bool available;
};
