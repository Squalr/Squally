#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

class AttackMenu;
class ClickableTextNode;
class ItemsMenu;
class PlatformerAttack;
class RadialScrollMenu;
class TimelineEntry;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create();

private:
	typedef SmartNode super;
	ChoicesMenu();
	virtual ~ChoicesMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();
	void setSelectedEntry(TimelineEntry* selectedEntry);

	CombatEvents::MenuStateArgs::CurrentMenu previousMenu;
	CombatEvents::MenuStateArgs::CurrentMenu currentMenu;

	RadialScrollMenu* choicesMenu;
	AttackMenu* attackMenu;
	ItemsMenu* itemsMenu;

	ClickableTextNode* itemsButton;
	ClickableTextNode* attackButton;
	ClickableTextNode* defendButton;
	
	TimelineEntry* selectedEntry;
	
	bool noItems;
	bool noDefend;

	static const float Radius;
};
