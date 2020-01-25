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

class CraftingMenu : public SmartNode
{
public:
	static CraftingMenu* create();

	void open();
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
	void tryCraftItem(Item* item);
	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* craftingWindow;
	cocos2d::Sprite* anvil;
	LocalizedLabel* craftingLabel;
	CraftingPreview* craftingPreview;
	CraftFilterMenu* filterMenu;
	ItemMenu* itemMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	CurrencyInventory* currencyInventory;
	Inventory* inventory;

	std::function<void()> returnClickCallback;
	bool equipmentChanged;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
