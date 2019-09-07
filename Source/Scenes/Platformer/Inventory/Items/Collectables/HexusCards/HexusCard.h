#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/CollectableItem.h"

class LocalizedString;

class HexusCard : public CollectableItem
{
public:

protected:
	HexusCard(CurrencyInventory* cost);
	~HexusCard();

private:
	typedef CollectableItem super;
};
