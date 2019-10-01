#pragma once

#include "Engine/Inventory/ItemPool.h"

class EquipmentInventory;
class HexusCard;
class Inventory;

class CardPool : public ItemPool
{
public:
	Item* getCard();
	std::vector<Item*> getCards();

protected:
	CardPool(int minCards, int maxCards);
	~CardPool();

private:
	typedef ItemPool super;

	int remainingCards;

	EquipmentInventory* equipmentInventory;
	Inventory* inventory;
};
