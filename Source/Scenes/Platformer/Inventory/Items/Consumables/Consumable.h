#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class Consumable : public Item
{
public:

protected:
	Consumable(LocalizedString* name, std::string iconResource);
	virtual ~Consumable();

private:
	typedef Item super;
};
