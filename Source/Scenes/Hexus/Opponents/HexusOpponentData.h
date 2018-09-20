#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

class HexusOpponentData
{
public:
	std::string animationResourceFile;
	std::string enemyNameKey;
	float animationScale;
	Vec2 animationOffset;
	Deck* deck;

protected:
	HexusOpponentData(std::string animationResourceFile, float animationScale, Vec2 animationOffset, std::string enemyNameKey, Card::CardStyle cardStyle, std::vector<CardData*> cards);
	~HexusOpponentData();

};
