#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

class CardRow : public SmartNode
{
public:
	static CardRow * create(bool isPlayerRow = true);

	void insertCard(Card* card, float cardInsertDelay);
	Card* removeCard(Card* card);
	int getCardCount();
	int getRowAttack();
	bool isPlayerRow();
	bool isEnemyRow();
	void setCardScale(float scale, float scaleSpeed);
	float getCardScale();
	void enableRowSelection(std::function<void(CardRow*)> callback);
	void enableRowCardSelection(std::function<void(Card*)> callback);
	void disableRowSelection();
	void disableRowCardSelection();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);
	void enableRowCardInteraction();
	void disableRowCardInteraction();
	int simulateCardEffect(Card *card);
	void setRowWidth(float newRowWidth, float duration);
	void clear();

	std::vector<Card*>* rowCards;

private:
	CardRow(bool isPlayerRow);
	~CardRow();

	void initializeListeners() override;
	void setCardPositions(float cardRepositionDelay);
	void onRowSelectClick(MenuSprite* menuSprite);

	float rowWidth;
	float cardScale;
	bool belongsToPlayer;
	MenuSprite* rowSelectSprite;
	std::function<void(CardRow*)> rowSelectCallback;
};
