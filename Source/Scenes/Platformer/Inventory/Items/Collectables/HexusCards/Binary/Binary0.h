#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary0 : public HexusCard
{
public:

protected:
	Binary0(CurrencyInventory* cost);
	~Binary0();

private:
	typedef HexusCard super;
};
