#include "HexusOpponentData.h"

HexusOpponentData::HexusOpponentData(
	std::string animationResourceFile,
	std::string backgroundResourceFile,
	float animationScale,
	Vec2 animationOffset,
	Vec2 avatarOffset,
	std::string enemyNameKey,
	HexusOpponentData::Difficulty difficulty,
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

std::vector<CardData*> HexusOpponentData::generateDeck(int deckSize, int minAttack, int maxAttack, float binaryRatio, float decimalRatio, std::vector<CardData*> guaranteedCards)
{
	maxAttack = MathUtils::clamp(maxAttack, 0, 15);
	minAttack = MathUtils::clamp(minAttack, maxAttack, 15);
	binaryRatio = MathUtils::clamp(binaryRatio, 0.0f, 1.0f);
	decimalRatio = MathUtils::clamp(decimalRatio, 0.0f, 1.0f);
	float hexRatio = MathUtils::clamp(binaryRatio, 0.0f, 1.0f + (binaryRatio + decimalRatio));
	float total = binaryRatio + decimalRatio + hexRatio;

	if (total == 0.0f)
	{
		return guaranteedCards;
	}

	std::vector<CardData*> deck = std::vector<CardData*>();

	for (auto it = guaranteedCards.begin(); it != guaranteedCards.end(); it++)
	{
		deck.push_back(*it);
		deckSize--;
	}

	int binaryCardCount = (binaryRatio / total) * deckSize;
	int decimalCardCount = (decimalRatio / total) * deckSize;
	int hexCardCount = (hexRatio / total) * deckSize;

	int nextAttack = maxAttack;

	while (binaryCardCount > 0)
	{
		if (nextAttack < minAttack)
		{
			nextAttack = maxAttack;
		}

		switch (nextAttack)
		{
			case 0:
			default:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary0));
				break;
			case 1:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary1));
				break;
			case 2:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary2));
				break;
			case 3:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary3));
				break;
			case 4:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary4));
				break;
			case 5:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary5));
				break;
			case 6:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary6));
				break;
			case 7:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary7));
				break;
			case 8:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary8));
				break;
			case 9:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary9));
				break;
			case 10:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary10));
				break;
			case 11:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary11));
				break;
			case 12:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary12));
				break;
			case 13:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary13));
				break;
			case 14:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary14));
				break;
			case 15:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Binary15));
				break;
		}

		nextAttack--;
		binaryCardCount--;
	}

	nextAttack = maxAttack;

	while (decimalCardCount > 0)
	{
		if (nextAttack < minAttack)
		{
			nextAttack = maxAttack;
		}

		switch (nextAttack)
		{
			case 0:
			default:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal0));
				break;
			case 1:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal1));
				break;
			case 2:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal2));
				break;
			case 3:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal3));
				break;
			case 4:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal4));
				break;
			case 5:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal5));
				break;
			case 6:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal6));
				break;
			case 7:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal7));
				break;
			case 8:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal8));
				break;
			case 9:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal9));
				break;
			case 10:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal10));
				break;
			case 11:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal11));
				break;
			case 12:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal12));
				break;
			case 13:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal13));
				break;
			case 14:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal14));
				break;
			case 15:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Decimal15));
				break;
		}

		nextAttack--;
		decimalCardCount--;
	}

	nextAttack = maxAttack;

	while (hexCardCount > 0)
	{
		if (nextAttack < 0)
		{
			nextAttack = maxAttack;
		}

		switch (nextAttack)
		{
			case 0:
			default:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex0));
				break;
			case 1:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex1));
				break;
			case 2:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex2));
				break;
			case 3:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex3));
				break;
			case 4:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex4));
				break;
			case 5:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex5));
				break;
			case 6:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex6));
				break;
			case 7:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex7));
				break;
			case 8:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex8));
				break;
			case 9:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex9));
				break;
			case 10:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex10));
				break;
			case 11:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex11));
				break;
			case 12:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex12));
				break;
			case 13:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex13));
				break;
			case 14:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex14));
				break;
			case 15:
				deck.push_back(CardList::getInstance()->cardListByName->at(CardKeys::Hex15));
				break;
		}

		nextAttack--;
		hexCardCount--;
	}

	return deck;
}