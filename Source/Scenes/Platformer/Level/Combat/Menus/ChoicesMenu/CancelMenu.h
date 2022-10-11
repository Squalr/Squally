#pragma once

#include "Engine/SmartNode.h"
#include "Events/CombatEvents.h"

class PlatformerEntity;
class RadialEntry;
class RadialScrollMenu;

class CancelMenu : public SmartNode
{
public:
	static CancelMenu* create();

protected:
	CancelMenu();
	virtual ~CancelMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef SmartNode super;

	void onCancelClick();
	void track(PlatformerEntity* trackTarget);
	
	CombatEvents::MenuStateArgs::CurrentMenu previousMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	CombatEvents::MenuStateArgs::CurrentMenu currentMenu = CombatEvents::MenuStateArgs::CurrentMenu::Closed;
	
	RadialScrollMenu* cancelMenu = nullptr;
	RadialEntry* cancelButton = nullptr;
	TimelineEntry* selectedEntry = nullptr;
	PlatformerEntity* trackTarget = nullptr;

	static const float Radius;
};
