#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class FilterEntry;
class Item;
class LocalizedLabel;
class SmartClippingNode;

class FilterMenu : public SmartNode
{
public:
	static FilterMenu* create();

	void focus();
	void unfocus();

protected:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	FilterMenu();
	~FilterMenu();

	void scrollFilterUp();
	void scrollFilterDown();
	void positionFilterText();

	SmartClippingNode* filterNode;
	cocos2d::Node* filterNodeContent;
	cocos2d::Sprite* selectedFilterRowActive;
	cocos2d::Sprite* selectedFilterRowInactive;
	cocos2d::Sprite* filterSelectionArrow;
	std::vector<FilterEntry*> filters;

	bool isFocused;
	int filterSelectionIndex;

	static const float LabelSpacing;
};
