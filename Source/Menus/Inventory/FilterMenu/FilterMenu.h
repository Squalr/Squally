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
	static FilterMenu* create(std::function<void()> onFilterChange);
	
	void focus();
	void unfocus();
	FilterEntry* getActiveFilter();

protected:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	FilterMenu(std::function<void()> onFilterChange);
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
	std::function<void()> onFilterChange;

	static const float LabelSpacing;
};
