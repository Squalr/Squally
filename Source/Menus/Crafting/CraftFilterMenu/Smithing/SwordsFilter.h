#pragma once

#include "Menus/Crafting/CraftFilterMenu/CraftFilterEntry.h"

class Item;
class LocalizedLabel;

class SwordsFilter : public CraftFilterEntry
{
public:
	static SwordsFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	SwordsFilter();
	virtual ~SwordsFilter();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef CraftFilterEntry super;
};
