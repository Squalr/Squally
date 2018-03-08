#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/Card.h"
#include "Minigames/Hexium/Config.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class CardRow : public Node
{
public:
	static CardRow * create();

	void insertCard(Card* card, float cardInsertDelay);
	Card* removeCard(Card* card);
	int getCardCount();
	int getRowAttack();
	void enableRowSelection(std::function<void(CardRow*)> callback);
	void enableRowCardSelection(std::function<void(Card*)> callback);
	void disableRowSelection();
	void setRowWidth(float newRowWidth);
	void clear();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);

	std::vector<Card*>* rowCards;

private:
	CardRow();
	~CardRow();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void setCardPositions(float cardRepositionDelay);
	void onRowSelectClick(MenuSprite* menuSprite);

	float rowWidth;
	MenuSprite* rowSelectSprite;
	std::function<void(CardRow*)> rowSelectCallback;
};

