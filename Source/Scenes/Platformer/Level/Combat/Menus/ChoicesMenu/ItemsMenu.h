#pragma once

#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/RadialScrollMenu.h"

class TimelineEntry;

class ItemsMenu : public RadialScrollMenu
{
public:
	static ItemsMenu* create();

	bool hasItems();
	void buildItemList(TimelineEntry* entry);

protected:
	ItemsMenu();
	virtual ~ItemsMenu();

private:
	typedef RadialScrollMenu super;

	bool hasItemsInList;

	static const float Radius;
};
