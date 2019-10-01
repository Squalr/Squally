#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class HexusCard : public Equipable
{
public:
	virtual std::string getCardKey() = 0;

protected:
	HexusCard(CurrencyInventory* cost);
	~HexusCard();

private:
	typedef Equipable super;
};
