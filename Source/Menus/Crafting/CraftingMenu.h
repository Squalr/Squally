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

class CraftingMenu : public SmartNode
{
public:
	static CraftingMenu* create();

	void open(std::vector<Item*> recipes);
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CraftingMenu();
	virtual ~CraftingMenu();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onFilterChange();
	void populateItemList();
	void onCraftPreview(Item* item);
	void tryCraftItem();
	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* craftingWindow;
	cocos2d::Sprite* anvil;
	LocalizedLabel* craftingLabel;
	CraftingPreview* craftingPreview;
	cocos2d::Sprite* craftButtonDisabled;
	ClickableNode* craftButton;
	CraftFilterMenu* filterMenu;
	ItemMenu* itemMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	std::vector<Item*> recipes;
	CurrencyInventory* currencyInventory;
	Inventory* inventory;

	std::function<void()> returnClickCallback;
	bool equipmentChanged;
};
