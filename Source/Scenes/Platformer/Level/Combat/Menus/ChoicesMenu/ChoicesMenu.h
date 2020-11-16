#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

class AttackMenu;
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

	CombatEvents::MenuStateArgs::CurrentMenu previousMenu;
	CombatEvents::MenuStateArgs::CurrentMenu currentMenu;

	RadialScrollMenu* choicesMenu;
	AttackMenu* attackMenu;
	ItemsMenu* itemsMenu;

	RadialEntry* itemsButton;
	RadialEntry* attackButton;
	RadialEntry* defendButton;
	
	TimelineEntry* selectedEntry;
	PlatformerEntity* trackTarget;

	bool noItems;
	bool noDefend;

	static const float Radius;
};
