#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;

class AllFilter : public FilterEntry
{
public:
	static AllFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	AllFilter();
	virtual ~AllFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
};
