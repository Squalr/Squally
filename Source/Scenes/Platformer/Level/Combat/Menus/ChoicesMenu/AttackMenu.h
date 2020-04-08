#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class PlatformerAttack;
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

	void selectAttack(TimelineEntry* entry, PlatformerAttack* attack, int index);

	static const float Radius;
};
