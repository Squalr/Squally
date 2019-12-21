#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class TimelineEntry;

class ItemsMenu : public RadialScrollMenu
{
public:
	static ItemsMenu* create();

	void buildAttackList(TimelineEntry* entry);

private:
	typedef RadialScrollMenu super;
	ItemsMenu();
	virtual ~ItemsMenu();

	static const float Radius;
};
