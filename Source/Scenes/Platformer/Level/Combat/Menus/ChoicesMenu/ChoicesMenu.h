#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

class AttackMenu;
class DefendMenu;
class ItemsMenu;
class PlatformerEntity;
class RadialEntry;
class RadialScrollMenu;
class Timeline;
class TimelineEntry;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create(Timeline* timelineRef);

protected:
	ChoicesMenu(Timeline* timelineRef);
	virtual ~ChoicesMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;
	
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();
	void setSelectedEntry(TimelineEntry* selectedEntry);
	void track(PlatformerEntity* trackTarget);

	CombatEvents::MenuStateArgs::CurrentMenu previousMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	CombatEvents::MenuStateArgs::CurrentMenu currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;

	RadialScrollMenu* choicesMenu = nullptr;
	AttackMenu* attackMenu = nullptr;
	DefendMenu* defendMenu = nullptr;
	ItemsMenu* itemsMenu = nullptr;

	RadialEntry* itemsButton = nullptr;
	RadialEntry* attackButton = nullptr;
	RadialEntry* defendButton = nullptr;
	
	TimelineEntry* selectedEntry = nullptr;
	PlatformerEntity* trackTarget = nullptr;

	bool noItems = false;
	bool noDefend = false;

	static const float Radius;
};
