#pragma once

#include "Engine/SmartNode.h"

class ConstantString;
class Inventory;
class LocalizedLabel;
class LocalizedString;
class Recipe;

class CraftingPreview : public SmartNode
{
public:
	static CraftingPreview* create();

	Recipe* getCurrentRecipe();
	bool preview(Recipe* recipe, Inventory* inventory);
	void refresh();
	void clearPreview();

protected:
	typedef SmartNode super;

	CraftingPreview();
	virtual ~CraftingPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	cocos2d::Node* previewNode;
	Inventory* inventory;
	Recipe* recipe;

	static const int MaxStatlines;
};
