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
class LocalizedLabel;
class LocalizedString;

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
	void positionScrolls();
	ClickableTextNode* buildMenuLabel(LocalizedString* text);

	cocos2d::Sprite* inventoryWindow;
	cocos2d::Sprite* equipmentPanel;
	LocalizedLabel* inventoryLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	ActiveFocus activeFocus;
	ActiveFilter activeFilter;
	cocos2d::Sprite* filterSelectionArrow;
	cocos2d::Sprite* filterSelectedArrow;
	cocos2d::Sprite* inventorySelectionArrow;

	cocos2d::Node* filterNode;
	cocos2d::Node* filterNodeContent;
	cocos2d::Node* inventoryNode;
	cocos2d::Node* inventoryNodeContent;
	ClickableTextNode* allLabel;
	ClickableTextNode* equipmentLabel;
	ClickableTextNode* consumablesLabel;
	ClickableTextNode* craftingLabel;
	ClickableTextNode* miscLabel;

	std::vector<ClickableTextNode*> filterLabels;

	std::function<void()> returnClickCallback;
};
