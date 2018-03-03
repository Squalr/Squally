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
	int getCardCount();
	void clear();
	void setMouseOverCallback(std::function<void(Card*)> callback);

private:
	Hand();
	~Hand();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void setCardPositions(float cardRepositionDelay);

	std::vector<Card*>* handCards;
	std::function<void(Card*)> mouseOverCallback;
};

