#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;
class LocalizedLabel;

class EquipmentFilter : public FilterEntry
{
public:
	static EquipmentFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
	EquipmentFilter();
	virtual ~EquipmentFilter();
};
