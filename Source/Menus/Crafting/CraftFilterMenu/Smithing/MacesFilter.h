#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class MacesFilter : public CraftFilterEntry
{
public:
	static MacesFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	MacesFilter();
	virtual ~MacesFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
