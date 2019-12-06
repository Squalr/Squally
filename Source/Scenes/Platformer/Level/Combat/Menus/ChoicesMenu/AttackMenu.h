#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class TimelineEntry;

class AttackMenu : public RadialScrollMenu
{
public:
	static AttackMenu* create();

	void buildAttackList(TimelineEntry* entry);

private:
	typedef RadialScrollMenu super;
	AttackMenu();
	virtual ~AttackMenu();

	static const float Radius;
};
