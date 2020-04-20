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

	RadialScrollMenu* cancelMenu;
	RadialEntry* cancelButton;
	
	CombatEvents::MenuStateArgs::CurrentMenu previousMenu;
	CombatEvents::MenuStateArgs::CurrentMenu currentMenu;
	
	TimelineEntry* selectedEntry;
	PlatformerEntity* trackTarget;

	static const float Radius;
};
