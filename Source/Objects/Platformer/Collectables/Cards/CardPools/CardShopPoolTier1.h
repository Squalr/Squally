#pragma once

#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"

class CardShopPoolTier1 : public CardPool
{
public:
	static CardShopPoolTier1* create();

protected:
	CardShopPoolTier1();
	~CardShopPoolTier1();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef CardPool super;
};
