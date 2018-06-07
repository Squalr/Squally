#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Utils/GameUtils.h"

#include "Card.h"
#include "Config.h"

using namespace cocos2d;

class CardRow : public Node
{
public:
	static CardRow * create();

	void insertCard(Card* card, float cardInsertDelay);
	Card* removeCard(Card* card);
	int getCardCount();
	int getRowAttack();
	void setCardScale(float scale, float scaleSpeed);
	float getCardScale();
	void enableRowSelection(std::function<void(CardRow*)> callback);
	void enableRowCardSelection(std::function<void(Card*)> callback);
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);
	void disableRowSelection();
	void disableRowCardSelection();
	void setRowWidth(float newRowWidth, float duration);
	void clear();

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
	float cardScale;
	MenuSprite* rowSelectSprite;
	std::function<void(CardRow*)> rowSelectCallback;
};

