#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;
class LocalizedLabel;

class AllFilter : public FilterEntry
{
public:
	static AllFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
	AllFilter();
	virtual ~AllFilter();
};
