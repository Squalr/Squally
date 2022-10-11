#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CraftFilterEntry;
class SmartClippingNode;

class CraftFilterMenu : public SmartNode
{
public:
	static CraftFilterMenu* create(std::function<void()> onFilterChange);
	
	void focus();
	void unfocus();
	void addFilter(CraftFilterEntry* entry);
	CraftFilterEntry* getActiveFilter();

protected:
	CraftFilterMenu(std::function<void()> onFilterChange);
	virtual ~CraftFilterMenu();

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
	std::vector<CraftFilterEntry*> filters;

	bool isFocused = true;
	int filterSelectionIndex = 0;
	std::function<void()> onFilterChange = nullptr;

	static const float LabelSpacing;
	static const cocos2d::CSize ClipSize;
};
