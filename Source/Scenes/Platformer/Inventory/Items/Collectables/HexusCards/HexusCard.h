#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class HexusCard : public Equipable
{
public:
	virtual std::string getCardKey() = 0;

protected:
	HexusCard(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~HexusCard();

private:
	typedef Equipable super;
};
