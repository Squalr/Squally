#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class WandsFilter : public CraftFilterEntry
{
public:
	static WandsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	WandsFilter();
	virtual ~WandsFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
