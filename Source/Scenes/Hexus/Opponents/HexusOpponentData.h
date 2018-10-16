#pragma once
#include "cocos2d.h"

#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

class HexusOpponentData
{
public:
	Deck* getDeck();

	enum Difficulty
	{
		Stupid,
		Easy,
		Medium,
		Hard,
		Expert,
	};

	std::string backgroundResourceFile;
	std::string animationResourceFile;
	std::string enemyNameKey;
	float animationScale;
	Vec2 animationOffset;
	Vec2 avatarOffset;
	std::vector<CardData*> rewards;

protected:
	HexusOpponentData(
		std::string animationResourceFile,
		std::string backgroundResourceFile,
		float animationScale,
		Vec2 animationOffset,
		Vec2 avatarOffset,
		std::string enemyNameKey,
		HexusOpponentData::Difficulty difficulty,
		Card::CardStyle cardStyle,
		std::vector<CardData*> rewards,
		std::vector<CardData*> cards);
	~HexusOpponentData();

	static std::vector<CardData*> generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards);

	Card::CardStyle cardStyle;
	std::vector<CardData*> cards;

private:
	static int getBestPossibleDeckAttack(int deckSize);
	static CardData* getBinaryCardForAttack(int attack);
	static CardData* getDecimalCardForAttack(int attack);
	static CardData* getHexCardForAttack(int attack);
};
