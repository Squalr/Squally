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

	void focus();
	void unfocus();
	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

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
	cocos2d::Node* contentNode;
	cocos2d::Sprite* selectedInventoryRow;
	int selectedItemIndex;
	cocos2d::Sprite* inventorySelectionArrow;

	SmartClippingNode* inventoryNode;
	cocos2d::Node* inventoryNodeContent;
	
	std::vector<cocos2d::Node*> equippedItemLabels;
	std::vector<cocos2d::Node*> itemLabels;

	bool isFocused;

	static const float LabelSpacing;
	static const cocos2d::Size LabelSize;
	static const int MinHexusCards;
};
