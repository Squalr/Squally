#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class TimelineEntry;

class AttackMenu : public RadialScrollMenu
{
public:
	static AttackMenu* create();

	void buildAttackList(TimelineEntry* entry);

protected:
	AttackMenu();
	virtual ~AttackMenu();

private:
	typedef RadialScrollMenu super;

	static const float Radius;
};
