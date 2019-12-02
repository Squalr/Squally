#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier1 : public MinMaxPool
{
public:
	static CardPoolTier1* create(int maxCards = 2);

protected:
	CardPoolTier1(int maxCards);
	~CardPoolTier1();

private:
	typedef MinMaxPool super;
};
