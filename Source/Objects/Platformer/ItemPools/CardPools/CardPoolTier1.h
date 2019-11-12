#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier1 : public MinMaxPool
{
public:
	static CardPoolTier1* create();

protected:
	CardPoolTier1();
	~CardPoolTier1();

private:
	typedef MinMaxPool super;
};
