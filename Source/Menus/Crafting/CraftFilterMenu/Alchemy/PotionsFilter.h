#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class PotionsFilter : public CraftFilterEntry
{
public:
	static PotionsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	PotionsFilter();
	virtual ~PotionsFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
