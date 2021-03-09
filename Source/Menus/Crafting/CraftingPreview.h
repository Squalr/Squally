#pragma once

#include "Engine/SmartNode.h"

class Inventory;
class Item;
class LocalizedString;
class Recipe;

class CraftingPreview : public SmartNode
{
public:
	static CraftingPreview* create();

	enum class DisplayMode
	{
		RequiredItems,
		ProducedItems,
	};

	Recipe* getCurrentRecipe();
	bool preview(Recipe* recipe, Inventory* inventory);
	void refresh();
	void clearPreview();
	void setDisplayMode(DisplayMode displayMode);

protected:
	typedef SmartNode super;

	CraftingPreview();
	virtual ~CraftingPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	void buildPreview(Item* item, LocalizedString* text, int index, bool isValid);

	cocos2d::Node* previewNode;
	Inventory* inventory;
	Recipe* recipe;
	DisplayMode displayMode = DisplayMode::RequiredItems;

	static const int MaxStatlines;
};
