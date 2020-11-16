#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;

class CraftingFilter : public FilterEntry
{
public:
	static CraftingFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	CraftingFilter();
	virtual ~CraftingFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
};
