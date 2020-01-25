#pragma once

#include "Engine/SmartNode.h"

class ConstantString;
class LocalizedLabel;
class LocalizedString;
class Recipe;

class CraftingPreview : public SmartNode
{
public:
	static CraftingPreview* create();

	void preview(Recipe* recipe);
	void clearPreview();

protected:
	typedef SmartNode super;
	
	CraftingPreview();
	virtual ~CraftingPreview();

	void onEnter() override;
	void initializePositions() override;

private:

	cocos2d::Node* previewNode;

	static const int MaxStatlines;
};
