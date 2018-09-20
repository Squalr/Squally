#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

class HexusOpponent
{
public:
	std::string animationResourceFile;
	std::string enemyName;

private:
	HexusOpponent(std::string animationResourceFile, std::string enemyName, Card::CardStyle cardStyle, std::vector<CardData*>* cards);
	~HexusOpponent();

	Deck* deck;
};

