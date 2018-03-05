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
	void enableRowSelection(std::function<void()> callback);
	void disableRowSelection();
	void setRowWidth(float newRowWidth);
	void clear();
	void disableInteraction();
	void enableInteraction();
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
	std::function<void()> rowSelectCallback;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseClickCallback;
};

