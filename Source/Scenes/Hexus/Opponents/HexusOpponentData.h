#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

class HexusOpponentData
{
public:
	Deck* getDeck();

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
		GameState::Difficulty difficulty,
		Card::CardStyle cardStyle,
		std::vector<CardData*> rewards,
		std::vector<CardData*> cards);
	~HexusOpponentData();

	Card::CardStyle cardStyle;
	std::vector<CardData*> cards;
};
