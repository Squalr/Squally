#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ConstantString;
class CurrencyInventory;
class LocalizedLabel;
class ItemPreview;
class Item;

class ShopItem : public GameObject
{
public:
	static ShopItem* create(cocos2d::ValueMap& properties);

	void activate();
	void deactivate();

	static const std::string MapKey;
	static const std::string PropertyShopPool;

protected:
	ShopItem(cocos2d::ValueMap& properties);
	virtual ~ShopItem();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	bool canSellItem();
	void sellItem();
	void removeShopItem();

	CurrencyInventory* playerCurrencyInventory;

	cocos2d::Node* activationNode = nullptr;
	cocos2d::Node* itemNode = nullptr;
	ClickableNode* itemClickHitbox = nullptr;
	cocos2d::Sprite* currencySprite = nullptr;
	LocalizedLabel* itemCostLabel = nullptr;
	ConstantString* itemCostString = nullptr;

	std::string poolName;
	ItemPreview* itemPreview = nullptr;
	Item* item = nullptr;

	int itemCost = 0;
	bool available = false;
};
