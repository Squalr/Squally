#pragma once

#include "Engine/Inventory/ItemPool.h"

class HexusCard;

class CardPool : public ItemPool
{
public:
	HexusCard* getCardFromPool();

protected:
	CardPool(int maxCards = 256);
	~CardPool();

private:
	typedef ItemPool super;

	int takenCards;
	int maxCards;
};
