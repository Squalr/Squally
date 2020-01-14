#pragma once

#include "Menus/Inventory/FilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class SwordsFilter : public CraftFilterEntry
{
public:
	static SwordsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
	SwordsFilter();
	virtual ~SwordsFilter();
};
