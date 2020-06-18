#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerEntity;

class CombatObject : public HackableObject
{
public:
protected:
	CombatObject(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline);
	virtual ~CombatObject();

	void onEnter() override;
	void update(float dt) override;
	void enableUpdate();
	void disableUpdate();

	PlatformerEntity* caster;
	PlatformerEntity* target;
	bool canUpdate;
	bool onTimeline;
	bool timelinePaused;
	bool timelinePausedCinematic;

private:
	typedef HackableObject super;
	
	void updateObjectCanUpdate();
};
