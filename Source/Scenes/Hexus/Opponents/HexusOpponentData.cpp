#include "HexusOpponentData.h"

HexusOpponentData::HexusOpponentData(
	std::string animationResourceFile,
	float animationScale,
	Vec2 animationOffset,
	std::string enemyNameKey,
	Card::CardStyle cardStyle,
	std::vector<CardData*> cards)
{
	this->animationResourceFile = animationResourceFile;
	this->animationScale = animationScale;
	this->animationOffset = animationOffset;
	this->enemyNameKey = enemyNameKey;
	this->cardStyle = cardStyle;
	this->cards = cards;
}

HexusOpponentData::~HexusOpponentData()
{
}

Deck* HexusOpponentData::getDeck()
{
	return Deck::create(this->cardStyle, this->cards);
}
