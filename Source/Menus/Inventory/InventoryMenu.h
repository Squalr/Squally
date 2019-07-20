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
class Item;
class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;

class InventoryMenu : public SmartNode
{
public:
	static InventoryMenu* create();

	void setReturnCallback(std::function<void()> returnClickCallback);

	static const float LabelSpacing;
	static const cocos2d::Size LabelSize;

protected:
	InventoryMenu();
	~InventoryMenu();

private:
	typedef SmartNode super;
	enum ActiveFocus
	{
		Filter,
		Inventory
	};
	
	enum ActiveFilter
	{
		All,
		Equipment,
		Consumables,
		Crafting,
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
	ClickableTextNode* buildMenuLabel(LocalizedString* text);

	cocos2d::Sprite* inventoryWindow;
	cocos2d::Sprite* equipmentPanel;
	LocalizedLabel* inventoryLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	ActiveFocus activeFocus;
	ActiveFilter activeFilter;
	int selectedItemIndex;
	cocos2d::Sprite* filterSelectionArrow;
	cocos2d::Sprite* filterSelectedArrow;
	cocos2d::Sprite* inventorySelectionArrow;

	SmartClippingNode* filterNode;
	cocos2d::Node* filterNodeContent;
	SmartClippingNode* inventoryNode;
	cocos2d::Node* inventoryNodeContent;
	ClickableTextNode* allLabel;
	ClickableTextNode* equipmentLabel;
	ClickableTextNode* consumablesLabel;
	ClickableTextNode* craftingLabel;
	ClickableTextNode* miscLabel;

	std::vector<Item*> allItems;
	std::vector<Item*> equippedItems;
	std::vector<ClickableTextNode*> filterLabels;
	std::vector<ClickableTextNode*> equippedItemLabels;
	std::vector<ClickableTextNode*> itemLabels;

	std::function<void()> returnClickCallback;
};
