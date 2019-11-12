#pragma once

#include "Engine/Inventory/MinMaxPool.h"

class CardShopPoolTier1 : public MinMaxPool
{
public:
	static CardShopPoolTier1* create();

protected:
	CardShopPoolTier1();
	~CardShopPoolTier1();

private:
	typedef MinMaxPool super;
};
