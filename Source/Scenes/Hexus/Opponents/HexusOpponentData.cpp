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
	this->deck = Deck::create(cardStyle, cards);
	this->deck->retain();
}

HexusOpponentData::~HexusOpponentData()
{
	this->deck->release();
}
