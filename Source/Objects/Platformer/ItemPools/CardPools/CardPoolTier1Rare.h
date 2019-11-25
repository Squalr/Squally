#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier1Rare : public MinMaxPool
{
public:
	static CardPoolTier1Rare* create();

protected:
	CardPoolTier1Rare();
	~CardPoolTier1Rare();

private:
	typedef MinMaxPool super;
};
