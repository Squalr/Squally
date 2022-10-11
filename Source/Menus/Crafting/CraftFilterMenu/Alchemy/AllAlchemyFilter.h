#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class AllAlchemyFilter : public CraftFilterEntry
{
public:
	static AllAlchemyFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	AllAlchemyFilter();
	virtual ~AllAlchemyFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
