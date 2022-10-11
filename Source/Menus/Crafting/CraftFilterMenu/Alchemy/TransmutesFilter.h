#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;

class TransmutesFilter : public CraftFilterEntry
{
public:
	static TransmutesFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	TransmutesFilter();
	virtual ~TransmutesFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
