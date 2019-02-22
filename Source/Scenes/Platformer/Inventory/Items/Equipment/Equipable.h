#pragma once

#include "Engine/Inventory/Item.h"

class LocalizedString;

class Equipable : public Item
{
public:

protected:
	Equipable(LocalizedString* name, std::string iconResource);
	virtual ~Equipable();

private:
	typedef Item super;
};
