#pragma once

#include "Engine/Maps/GameObject.h"

class HexusCard;

class CardPool : public GameObject
{
public:
	HexusCard* getCardFromPool();

protected:
	CardPool();
	~CardPool();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void addCardToPool(HexusCard* item, float weight);

private:
	typedef GameObject super;

	void calculateWeightSum();

	cocos2d::Node* cardsNode;

	std::vector<std::tuple<HexusCard*, float>> itemPool;
	float weightSum;
};
