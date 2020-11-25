#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class Consumable;
class CurrencyInventory;
class EquipmentInventory;
class Item;
class ItemMenu;
class Inventory;
template <class T>
class LazyNode;
class LocalizedLabel;
class PartyMenu;
class FilterMenu;

class InventoryMenu : public SmartNode
{
public:
	static InventoryMenu* create(LazyNode<PartyMenu>* partyMenu);

	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	InventoryMenu(LazyNode<PartyMenu>* partyMenu);
	virtual ~InventoryMenu();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void onFilterChange();
	void populateItemList();
	void performEquipmentAction(Item* item);
	void performInventoryAction(Item* item);
	void equipItem(Item* item);
	void unequipItem(Item* item);
	void consumeItem(Consumable* item);
	void close();

	cocos2d::Sprite* inventoryWindow;
	LocalizedLabel* inventoryLabel;
	FilterMenu* filterMenu;
	ItemMenu* itemMenu;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	CurrencyInventory* currencyInventory;
	EquipmentInventory* equipmentInventory;
	Inventory* inventory;

	std::function<void()> returnClickCallback;
	bool equipmentChanged;

	LazyNode<PartyMenu>* partyMenu;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
