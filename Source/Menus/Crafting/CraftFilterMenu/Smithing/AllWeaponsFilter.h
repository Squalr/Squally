#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class AllWeaponsFilter : public CraftFilterEntry
{
public:
	static AllWeaponsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	AllWeaponsFilter();
	virtual ~AllWeaponsFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
