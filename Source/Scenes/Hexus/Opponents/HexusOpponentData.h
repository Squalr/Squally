#pragma once
#include <string>
#include <vector>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/Card.h"

class CardData;
class Deck;
class StateOverride;

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
		std::string animationResourceFile,
		std::string backgroundResourceFile,
		float animationScale,
		cocos2d::Vec2 animationOffset,
		cocos2d::Vec2 frameOffset,
		cocos2d::Vec2 avatarOffset,
		std::string enemyNameKey,
		HexusOpponentData::Strategy strategy,
		Card::CardStyle cardStyle,
		float strength,
		std::vector<CardData*> cards,
		std::vector<std::string> rewards,
		std::function<void(Result)> onRoundEnd = nullptr,
		StateOverride* stateOverride = nullptr);

	HexusOpponentData(
		std::string animationResourceFile,
		std::string backgroundResourceFile,
		float animationScale,
		cocos2d::Vec2 animationOffset,
		cocos2d::Vec2 frameOffset,
		cocos2d::Vec2 avatarOffset,
		std::string enemyNameKey,
		HexusOpponentData::Strategy strategy,
		Card::CardStyle cardStyle,
		float strength,
		std::vector<CardData*> cards,
		std::vector<std::string> rewards,
		std::function<void(Result)> onRoundEnd = nullptr,
		StateOverride* stateOverride = nullptr);
	~HexusOpponentData();

	Deck* getDeck();
	CardData* getStrongestCard();

	static int generateReward(float deckStrength);
	static std::vector<CardData*> generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards);
	void setIsLastInChapter();
	bool getIsLastInChapter();

	std::string backgroundResourceFile;
	std::string animationResourceFile;
	std::string enemyNameKey;
	float animationScale;
	cocos2d::Vec2 animationOffset;
	cocos2d::Vec2 avatarOffset;
	cocos2d::Vec2 frameOffset;
	float strength;
	int reward;
	Strategy strategy;
	std::vector<std::string> rewards;
	std::function<void(Result)> onRoundEnd;
	StateOverride* stateOverride;

	static const std::string winsPrefix;
	static const std::string lossesPrefix;

protected:
	Card::CardStyle cardStyle;
	std::vector<CardData*> cards;

private:
	static int getBestPossibleDeckAttack(int deckSize);
	static CardData* getBinaryCardForAttack(int attack);
	static CardData* getDecimalCardForAttack(int attack);
	static CardData* getHexCardForAttack(int attack);

	bool isLastInChapter;
};
