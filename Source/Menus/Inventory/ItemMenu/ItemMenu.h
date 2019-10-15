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
class FilterEntry;
class Inventory;
class Item;
class ItemPreview;
class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;

class ItemMenu : public SmartNode
{
public:
	static ItemMenu* create();

	void setVisibleItems(std::vector<Item*> visibleItems);
	void focus();
	void unfocus();

protected:
	ItemMenu();
	~ItemMenu();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void scrollInventoryUp();
	void scrollInventoryDown();
	void buildInventoryList();
	void updateAndPositionItemText();
	void toggleEquipSelectedItem();
	cocos2d::Node* buildMenuLabel(LocalizedString* text, cocos2d::Sprite* icon = nullptr);

	CurrencyInventory* currencyInventory;
	EquipmentInventory* equipmentInventory;
	Inventory* inventory;

	ItemPreview* itemPreview;
	cocos2d::Sprite* selectedInventoryRow;
	cocos2d::Sprite* inventorySelectionArrow;
	SmartClippingNode* itemListNode;
	cocos2d::Node* itemListNodeContent;

	std::vector<Item*> visibleItems;
	int selectedItemIndex;
	bool isFocused;

	static const float LabelSpacing;
	static const cocos2d::Size LabelSize;
	static const int MinHexusCards;
};
