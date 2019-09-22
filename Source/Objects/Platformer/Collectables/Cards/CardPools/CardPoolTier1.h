#pragma once

#include "Objects/Platformer/Collectables/Cards/CardPools/CardPool.h"

class CardPoolTier1 : public CardPool
{
public:
	static CardPoolTier1* create();

protected:
	CardPoolTier1();
	~CardPoolTier1();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef CardPool super;
};
