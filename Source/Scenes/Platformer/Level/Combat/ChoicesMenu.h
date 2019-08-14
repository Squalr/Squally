#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

namespace cocos2d
{
	class Node;
}

class ClickableTextNode;
class PlatformerAttack;
class TimelineEntry;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create(bool noItems = false, bool noDefend = false);

private:
	typedef SmartNode super;
	ChoicesMenu(bool noItems = false, bool noDefend = false);
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
	void buildAttackList(cocos2d::Node* nodeRef, std::vector<ClickableTextNode*>* listRef, std::vector<PlatformerAttack*> attacks, std::string backgroundResource);

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
	
	bool noItems;
	bool noDefend;

	static const float InnerChoicesRadius;
	static const float OuterChoicesRadius;
};
