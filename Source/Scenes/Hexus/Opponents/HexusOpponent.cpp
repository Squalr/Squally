#include "HexusOpponent.h"

HexusOpponent::HexusOpponent(std::string newCardResourceFile, std::string enemyName, std::vector<CardData*> cards)
{
	this->animationResourceFile = animationResourceFile;
	this->enemyName = enemyName;
	this->deck = Deck::create(Card::CardStyle::Shadow, cards);
}

HexusOpponent::~HexusOpponent()
{
}
