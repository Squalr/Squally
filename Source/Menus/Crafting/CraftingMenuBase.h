#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class CraftFilterMenu;
class CraftingPreview;
class CurrencyInventory;
class EquipmentInventory;
class Item;
class ItemMenu;
class Inventory;
class LocalizedLabel;
class Recipe;

class CraftingMenuBase : public SmartNode
{
public:
	void open(std::vector<Item*> recipes);
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CraftingMenuBase();
	virtual ~CraftingMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	virtual void onCraftPreview(Item* item);
	void tryCraftItem();
	
	CraftFilterMenu* filterMenu;
	cocos2d::Node* backDecorNode;

	bool canCraft;

private:
	typedef SmartNode super;

	void onFilterChange();
	void populateItemList();
	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* craftingWindow;
	LocalizedLabel* craftingLabel;
	CraftingPreview* craftingPreview;
	ItemMenu* itemMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	std::vector<Item*> recipes;
	CurrencyInventory* currencyInventory;
	Inventory* inventory;

	std::function<void()> returnClickCallback;
};
