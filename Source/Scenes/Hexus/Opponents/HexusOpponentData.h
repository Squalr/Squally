#pragma once
#include <string>
#include <vector>

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"

class CardData;
class Deck;
class StateOverride;

class HexusOpponentData
{
public:
	Deck* getDeck();
	CardData* getStrongestCard();

	enum Strategy
	{
		Random,
		StrongestCardsFirst,
		WeakestCardsFirst,
	};

	std::string backgroundResourceFile;
	std::string animationResourceFile;
	std::string enemyNameKey;
	float animationScale;
	cocos2d::Vec2 animationOffset;
	cocos2d::Vec2 avatarOffset;
	int reward;
	Strategy strategy;
	StateOverride* stateOverride;

	static const std::string winsPrefix;
	static const std::string lossesPrefix;

protected:
	HexusOpponentData(
		std::string animationResourceFile,
		std::string backgroundResourceFile,
		float animationScale,
		cocos2d::Vec2 animationOffset,
		cocos2d::Vec2 avatarOffset,
		std::string enemyNameKey,
		HexusOpponentData::Strategy strategy,
		Card::CardStyle cardStyle,
		int reward,
		std::vector<CardData*> cards,
		StateOverride* stateOverride = nullptr);
	~HexusOpponentData();

	static int generateReward(float deckStrength);
	static std::vector<CardData*> generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards);

	Card::CardStyle cardStyle;
	std::vector<CardData*> cards;

private:
	static int getBestPossibleDeckAttack(int deckSize);
	static CardData* getBinaryCardForAttack(int attack);
	static CardData* getDecimalCardForAttack(int attack);
	static CardData* getHexCardForAttack(int attack);
};
