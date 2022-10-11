#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class FilterEntry;
class SmartClippingNode;

class FilterMenu : public SmartNode
{
public:
	static FilterMenu* create(std::function<void()> onFilterChange);
	
	void focus();
	void unfocus();
	FilterEntry* getActiveFilter();

protected:
	FilterMenu(std::function<void()> onFilterChange);
	virtual ~FilterMenu();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void scrollFilterUp();
	void scrollFilterDown();
	void positionFilterText();

	SmartClippingNode* filterNode = nullptr;
	cocos2d::Node* filterNodeContent = nullptr;
	cocos2d::Sprite* selectedFilterRowActive = nullptr;
	cocos2d::Sprite* selectedFilterRowInactive = nullptr;
	cocos2d::Sprite* filterSelectionArrow = nullptr;
	std::vector<FilterEntry*> filters;

	bool isFocused = true;
	int filterSelectionIndex = 0;
	std::function<void()> onFilterChange = nullptr;

	static const float LabelSpacing;
};
