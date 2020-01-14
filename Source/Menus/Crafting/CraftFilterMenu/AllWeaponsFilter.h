#pragma once

#include "Menus/Inventory/FilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class AllWeaponsFilter : public CraftFilterEntry
{
public:
	static AllWeaponsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
	AllWeaponsFilter();
	virtual ~AllWeaponsFilter();
};
