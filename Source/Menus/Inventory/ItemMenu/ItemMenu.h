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
class ConfirmationMenu;
class CurrencyInventory;
class EquipmentInventory;
class Inventory;
class Item;
class ItemEntry;
class ItemPreview;
class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;

class ItemMenu : public SmartNode
{
public:
	static ItemMenu* create();

	void clearPreview();
	void clearVisibleItems();
	ItemEntry* pushVisibleItem(Item* visibleItem, std::function<void()> onToggle);
	void updateAndPositionItemText();
	void focus();
	void unfocus();

protected:
	ItemMenu();
	virtual ~ItemMenu();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void scrollInventoryUp();
	void scrollInventoryDown();

	CurrencyInventory* currencyInventory;
	EquipmentInventory* equipmentInventory;
	Inventory* inventory;

	ItemPreview* itemPreview;
	cocos2d::Sprite* selectedInventoryRow;
	cocos2d::Sprite* inventorySelectionArrow;
	SmartClippingNode* itemListNode;
	cocos2d::Node* itemListNodeContent;

	std::map<Item*, ItemEntry*> itemEntryMapping;
	std::vector<ItemEntry*> visibleItems;
	int selectedItemIndex;
	bool isFocused;

	static const float LabelSpacing;
	static const cocos2d::Size LabelSize;
};
