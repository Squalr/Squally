#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class PlatformerAttack;
class Timeline;
class TimelineEntry;

class DefendMenu : public RadialScrollMenu
{
public:
	static DefendMenu* create(Timeline* timelineRef);

	void buildAttackList(TimelineEntry* entry);

protected:
	DefendMenu(Timeline* timelineRef);
	virtual ~DefendMenu();

private:
	typedef RadialScrollMenu super;

	void selectAttack(TimelineEntry* entry, PlatformerAttack* attack, int index);

	Timeline* timelineRef = nullptr;

	static const float Radius;
};
