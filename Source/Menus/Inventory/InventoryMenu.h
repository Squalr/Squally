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
template <class T> class LazyNode;
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

	cocos2d::Sprite* inventoryWindow = nullptr;
	LocalizedLabel* inventoryLabel = nullptr;
	FilterMenu* filterMenu = nullptr;
	ItemMenu* itemMenu = nullptr;
	ClickableTextNode* returnButton = nullptr;
	ClickableNode* closeButton = nullptr;

	CurrencyInventory* currencyInventory = nullptr;
	EquipmentInventory* equipmentInventory = nullptr;
	Inventory* inventory = nullptr;

	std::function<void()> returnClickCallback = nullptr;
	bool equipmentChanged = false;

	LazyNode<PartyMenu>* partyMenu = nullptr;

	static const int MinHexusCards;
	static const int MaxHexusCards;
};
