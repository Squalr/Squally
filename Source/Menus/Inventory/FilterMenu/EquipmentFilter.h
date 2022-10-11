#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;

class EquipmentFilter : public FilterEntry
{
public:
	static EquipmentFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	EquipmentFilter();
	virtual ~EquipmentFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
};
