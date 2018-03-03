#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class CardRow : public Node
{
public:
	static CardRow * create();

	void insertCard(Card* card, float cardInsertDelay);
	Card* removeCard(Card* card);
	int getCardCount();
	void clear();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);

	static const float standardInsertDelay;

private:
	CardRow();
	~CardRow();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void setCardPositions(float cardRepositionDelay);

	std::vector<Card*>* rowCards;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseClickCallback;
};

