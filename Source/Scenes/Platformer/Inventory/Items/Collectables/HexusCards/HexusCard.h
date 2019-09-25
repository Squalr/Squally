#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

class LocalizedString;

class HexusCard : public Equipable
{
public:

protected:
	HexusCard(CurrencyInventory* cost);
	~HexusCard();

private:
	typedef Equipable super;
};
