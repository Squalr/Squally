#include "HexusOpponent.h"

HexusOpponent::HexusOpponent(std::string animationResourceFile, std::string enemyName, Card::CardStyle cardStyle, std::vector<CardData*>* cards)
{
	this->animationResourceFile = animationResourceFile;
	this->enemyName = enemyName;
	this->deck = Deck::create(Card::CardStyle::Shadow, cards);
}

HexusOpponent::~HexusOpponent()
{
}
