#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class PlatformerAttack;
class Timeline;
class TimelineEntry;

class AttackMenu : public RadialScrollMenu
{
public:
	static AttackMenu* create(Timeline* timelineRef);

	void buildAttackList(TimelineEntry* entry);

protected:
	AttackMenu(Timeline* timelineRef);
	virtual ~AttackMenu();

private:
	typedef RadialScrollMenu super;

	void selectAttack(TimelineEntry* entry, PlatformerAttack* attack, int index);

	Timeline* timelineRef;

	static const float Radius;
};
