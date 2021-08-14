#pragma once
#include <functional>

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
class Item;
class ItemMenu;
class Inventory;
class LocalizedLabel;
class LocalizedString;
class ProgressBar;
class Recipe;
class Sound;

class CraftingMenuBase : public SmartNode
{
public:
	virtual void open(const std::vector<Item*>& recipes);
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	CraftingMenuBase(LocalizedString* titleString);
	virtual ~CraftingMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	virtual void onCraftStart() = 0;
	virtual void onCraftEnd(bool viaCancel) = 0;
	virtual LocalizedString* getCraftString();
	void startCraft();
	void craftItem();
	
	CraftFilterMenu* filterMenu = nullptr;
	cocos2d::Node* backDecorNode = nullptr;
	cocos2d::Node* craftIconNode = nullptr;
	CraftingPreview* craftingPreview = nullptr;
	Item* selectedRecipe = nullptr;

private:
	typedef SmartNode super;

	int getCraftCount(Recipe* recipe, Inventory* inventory);
	void onCraftPreview(Item* item);
	void onCraftInteract();
	void stopCraft(bool viaCancel);
	void onFilterChange();
	void populateItemList();
	void close();

	cocos2d::LayerColor* backdrop = nullptr;
	cocos2d::Sprite* craftingWindow = nullptr;
	LocalizedLabel* craftingLabel = nullptr;
	ItemMenu* itemMenu = nullptr;
	ClickableNode* craftButton = nullptr;
	cocos2d::Sprite* craftButtonDisabled = nullptr;
	cocos2d::Sprite* cancelIcon = nullptr;
	ProgressBar* craftProgress = nullptr;
	ClickableTextNode* returnButton = nullptr;
	ClickableNode* closeButton = nullptr;

	Sound* errorSound = nullptr;

	std::vector<Item*> recipes;
	CurrencyInventory* currencyInventory = nullptr;
	Inventory* inventory = nullptr;

	bool canCraft = false;
	bool isCrafting = false;
	float craftElapsedTime = 0.0f;

	std::function<void()> returnClickCallback = nullptr;

	static const float CraftDuration;
};
