#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardPoolTier1Low : public MinMaxPool
{
public:
	static CardPoolTier1Low* create();

protected:
	CardPoolTier1Low();
	~CardPoolTier1Low();

private:
	typedef MinMaxPool super;
};
