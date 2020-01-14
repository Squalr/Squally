#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CraftFilterEntry;
class Item;
class LocalizedLabel;
class SmartClippingNode;

class CraftFilterMenu : public SmartNode
{
public:
	static CraftFilterMenu* create(std::function<void()> onFilterChange);
	
	void focus();
	void unfocus();
	CraftFilterEntry* getActiveFilter();

protected:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	CraftFilterMenu(std::function<void()> onFilterChange);
	virtual ~CraftFilterMenu();

	void scrollFilterUp();
	void scrollFilterDown();
	void positionFilterText();

	SmartClippingNode* filterNode;
	cocos2d::Node* filterNodeContent;
	cocos2d::Sprite* selectedFilterRowActive;
	cocos2d::Sprite* selectedFilterRowInactive;
	cocos2d::Sprite* filterSelectionArrow;
	std::vector<CraftFilterEntry*> filters;

	bool isFocused;
	int filterSelectionIndex;
	std::function<void()> onFilterChange;

	static const float LabelSpacing;
};
