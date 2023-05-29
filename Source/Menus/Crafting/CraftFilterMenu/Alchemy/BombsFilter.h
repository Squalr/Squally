#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class BombsFilter : public CraftFilterEntry
{
public:
	static BombsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	BombsFilter();
	virtual ~BombsFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
