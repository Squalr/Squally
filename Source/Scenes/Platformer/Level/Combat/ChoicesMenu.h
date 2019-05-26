#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

namespace cocos2d
{
	class Node;
}

class ClickableTextNode;
class TimelineEntry;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create();

private:
	typedef SmartNode super;
	ChoicesMenu();
	virtual ~ChoicesMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();
	void toggleInnerText(bool isVisible);
	void toggleOuterText(bool isVisible);
	void setSelectedEntry(TimelineEntry* selectedEntry);
	void buildAttackList();
	void buildItemList();

	CombatEvents::MenuStateArgs::CurrentMenu currentMenu;

	ClickableTextNode* itemsNode;
	ClickableTextNode* attackNode;
	ClickableTextNode* defendNode;
	cocos2d::Node* attackListNode;
	cocos2d::Node* itemListNode;
	cocos2d::Node* defendListNode;
	TimelineEntry* selectedEntry;

	std::vector<ClickableTextNode*> attackListNodes;
	std::vector<ClickableTextNode*> itemListNodes;

	static const float InnerChoicesRadius;
	static const float OuterChoicesRadius;
};
