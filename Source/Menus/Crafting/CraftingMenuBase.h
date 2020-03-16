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
class ProgressBar;
class Recipe;
class Sound;

class CraftingMenuBase : public SmartNode
{
public:
	void open(std::vector<Item*> recipes);
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CraftingMenuBase();
	virtual ~CraftingMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	virtual void onCraftStart() = 0;
	virtual void onCraftEnd(bool viaCancel) = 0;
	void startCraft();
	void craftItem();
	
	CraftFilterMenu* filterMenu;
	cocos2d::Node* backDecorNode;
	cocos2d::Node* craftIconNode;

private:
	typedef SmartNode super;

	void onCraftPreview(Item* item);
	void onCraftInteract();
	void stopCraft(bool viaCancel);
	void onFilterChange();
	void populateItemList();
	void close();

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* craftingWindow;
	LocalizedLabel* craftingLabel;
	CraftingPreview* craftingPreview;
	ItemMenu* itemMenu;
	ClickableNode* craftButton;
	cocos2d::Sprite* craftButtonDisabled;
	cocos2d::Sprite* cancelIcon;
	ProgressBar* craftProgress;
	ClickableTextNode* returnButton;
	ClickableNode* closeButton;

	Sound* errorSound;

	std::vector<Item*> recipes;
	CurrencyInventory* currencyInventory;
	Inventory* inventory;

	bool canCraft;
	bool isCrafting;
	float craftElapsedTime;

	std::function<void()> returnClickCallback;

	static const float CraftDuration;
};
