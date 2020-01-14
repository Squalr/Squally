#pragma once

#include "Menus/Inventory/FilterMenu/FilterEntry.h"

class Item;
class LocalizedLabel;

class ConsumablesFilter : public FilterEntry
{
public:
	static ConsumablesFilter* create();

	std::vector<Item*> filter(std::vector<Item*> itemList) override;

protected:
	void onEnter() override;
	void initializePositions() override;

private:
	typedef FilterEntry super;
	ConsumablesFilter();
	virtual ~ConsumablesFilter();
};
