#pragma once
#include <string>
#include <vector>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/Card.h"

class CardData;
class Deck;
class StateOverride;
class TutorialBase;

class HexusOpponentData : public SmartNode
{
public:
	enum Strategy
	{
		Random,
		StrongestCardsFirst,
		WeakestCardsFirst,
	};

	enum Result
	{
		Win,
		Loss,
		Draw,
	};

	static HexusOpponentData* create(
		cocos2d::Node* entityPreviewNode,
		std::string backgroundResourceFile,
		cocos2d::Vec2 avatarOffset,
		std::string enemyAnalyticsIdentifier,
		HexusOpponentData::Strategy strategy,
		Card::CardStyle cardStyle,
		std::vector<CardData*> cards,
		std::function<void(Result)> onRoundEnd = nullptr,
		StateOverride* stateOverride = nullptr,
		std::vector<TutorialBase*> tutorials = { }
	);

	HexusOpponentData(
		cocos2d::Node* entityPreviewNode,
		std::string backgroundResourceFile,
		cocos2d::Vec2 avatarOffset,
		std::string enemyAnalyticsIdentifier,
		HexusOpponentData::Strategy strategy,
		Card::CardStyle cardStyle,
		std::vector<CardData*> cards,
		std::function<void(Result)> onRoundEnd = nullptr,
		StateOverride* stateOverride = nullptr,
		std::vector<TutorialBase*> tutorials = { }
	);
	~HexusOpponentData();

	std::vector<CardData*> getDeck();
	CardData* getStrongestCard();

	static std::vector<CardData*> generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards);
	void setIsLastInChapter();
	bool getIsLastInChapter();

	cocos2d::Node* entityPreviewNode;
	std::string backgroundResourceFile;
	std::string enemyAnalyticsIdentifier;
	cocos2d::Vec2 avatarOffset;
	Strategy strategy;
	std::function<void(Result)> onRoundEnd;
	StateOverride* stateOverride;
	Card::CardStyle cardStyle;
	std::vector<TutorialBase*> tutorials;

	static const std::string winsPrefix;
	static const std::string lossesPrefix;

protected:
	std::vector<CardData*> cards;

private:
	static int getBestPossibleDeckAttack(int deckSize);
	static CardData* getBinaryCardForAttack(int attack);
	static CardData* getDecimalCardForAttack(int attack);
	static CardData* getHexCardForAttack(int attack);

	bool isLastInChapter;
};
