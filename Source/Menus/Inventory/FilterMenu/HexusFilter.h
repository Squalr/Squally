#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;
class LocalizedLabel;

class HexusFilter : public FilterEntry
{
public:
	static HexusFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
	HexusFilter();
	virtual ~HexusFilter();
};
