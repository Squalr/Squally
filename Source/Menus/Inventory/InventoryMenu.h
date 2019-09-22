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
class ItemPreview;
class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;

class InventoryMenu : public SmartNode
{
public:
	static InventoryMenu* create();

	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

	static const float LabelSpacing;
	static const cocos2d::Size LabelSize;

protected:
	InventoryMenu();
	~InventoryMenu();

private:
	typedef SmartNode super;
	enum class ActiveFocus
	{
		Filter,
		Inventory
	};
	
	enum class ActiveFilter
	{
		All,
		Equipment,
		Consumables,
		Crafting,
		Hexus,
		Misc
	};

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void setActiveFilter(ActiveFilter activeFilter);
	void scrollFilterUp();
	void scrollFilterDown();
	void scrollInventoryUp();
	void scrollInventoryDown();
	void unfocusInventory();
	void focusInventory();
	void buildInventoryList();
	void positionFilterText();
	void updateAndPositionItemText();
	void toggleEquipSelectedItem();
	cocos2d::Node* buildMenuLabel(LocalizedString* text, cocos2d::Sprite* icon = nullptr);

	CurrencyInventory* currencyInventory;
	EquipmentInventory* equipmentInventory;
	Inventory* inventory;
	cocos2d::Sprite* inventoryWindow;
	cocos2d::Sprite* equipmentPanel;
	ItemPreview* itemPreview;
	cocos2d::Node* contentNode;
	cocos2d::Sprite* selectedFilterRowActive;
	cocos2d::Sprite* selectedFilterRowInactive;
	cocos2d::Sprite* selectedInventoryRow;
	LocalizedLabel* inventoryLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	ActiveFocus activeFocus;
	ActiveFilter activeFilter;
	int selectedItemIndex;
	cocos2d::Sprite* filterSelectionArrow;
	cocos2d::Sprite* inventorySelectionArrow;

	SmartClippingNode* filterNode;
	cocos2d::Node* filterNodeContent;
	SmartClippingNode* inventoryNode;
	cocos2d::Node* inventoryNodeContent;
	cocos2d::Node* allLabel;
	cocos2d::Node* equipmentLabel;
	cocos2d::Node* consumablesLabel;
	cocos2d::Node* craftingLabel;
	cocos2d::Node* hexusLabel;
	cocos2d::Node* miscLabel;

	std::vector<Item*> inventoryItems;
	std::vector<Item*> equippedItems;
	std::vector<cocos2d::Node*> filterLabels;
	std::vector<cocos2d::Node*> equippedItemLabels;
	std::vector<cocos2d::Node*> itemLabels;

	std::function<void()> returnClickCallback;
};
