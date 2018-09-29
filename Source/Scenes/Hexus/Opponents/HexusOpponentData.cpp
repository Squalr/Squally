#include "HexusOpponentData.h"

HexusOpponentData::HexusOpponentData(
	std::string animationResourceFile,
	std::string backgroundResourceFile,
	float animationScale,
	Vec2 animationOffset,
	Vec2 avatarOffset,
	std::string enemyNameKey,
	Card::CardStyle cardStyle,
	std::vector<CardData*> rewards,
	std::vector<CardData*> cards)
{
	this->animationResourceFile = animationResourceFile;
	this->backgroundResourceFile = backgroundResourceFile;
	this->animationScale = animationScale;
	this->animationOffset = animationOffset;
	this->avatarOffset = avatarOffset;
	this->enemyNameKey = enemyNameKey;
	this->cardStyle = cardStyle;
	this->rewards = rewards;
	this->cards = cards;
}

HexusOpponentData::~HexusOpponentData()
{
}

Deck* HexusOpponentData::getDeck()
{
	return Deck::create(this->cardStyle, this->cards);
}
