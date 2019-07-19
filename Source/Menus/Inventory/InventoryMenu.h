#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
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

protected:
	InventoryMenu();
	~InventoryMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	
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

	cocos2d::Sprite* inventoryWindow;
	cocos2d::Sprite* equipmentPanel;
	LocalizedLabel* inventoryLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	ActiveFocus activeFocus;

	cocos2d::Node* filterNode;
	ClickableTextNode* allLabel;
	ClickableTextNode* equipmentLabel;
	ClickableTextNode* consumablesLabel;
	ClickableTextNode* craftingLabel;
	ClickableTextNode* miscLabel;

	ClickableTextNode* buildMenuLabel(LocalizedString* text);

	std::function<void()> returnClickCallback;
};
