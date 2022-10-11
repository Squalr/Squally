#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class AllEquipmentFilter : public CraftFilterEntry
{
public:
	static AllEquipmentFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	AllEquipmentFilter();
	virtual ~AllEquipmentFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
