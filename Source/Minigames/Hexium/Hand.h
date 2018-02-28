#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class Hand : public Node
{
public:
	static Hand * create();

	void insertCard(Card* card, float cardInsertDelay);
	void clear();

private:
	Hand();
	~Hand();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();

	std::vector<Card*>* handCards;
};

