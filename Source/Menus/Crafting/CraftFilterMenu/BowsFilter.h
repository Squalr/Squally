#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class BowsFilter : public CraftFilterEntry
{
public:
	static BowsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
	BowsFilter();
	virtual ~BowsFilter();
};
