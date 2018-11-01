#include "HexusOpponentData.h"

const std::string HexusOpponentData::winsPrefix = "WINS_";
const std::string HexusOpponentData::lossesPrefix = "LOSSES_";

HexusOpponentData::HexusOpponentData(
	std::string animationResourceFile,
	std::string backgroundResourceFile,
	float animationScale,
	Vec2 animationOffset,
	Vec2 avatarOffset,
	std::string enemyNameKey,
	HexusOpponentData::Difficulty difficulty,
	Card::CardStyle cardStyle,
	int reward,
	std::vector<CardData*> cards)
{
	this->animationResourceFile = animationResourceFile;
	this->backgroundResourceFile = backgroundResourceFile;
	this->animationScale = animationScale;
	this->animationOffset = animationOffset;
	this->avatarOffset = avatarOffset;
	this->enemyNameKey = enemyNameKey;
	this->cardStyle = cardStyle;
	this->reward = reward;
	this->cards = cards;
}

HexusOpponentData::~HexusOpponentData()
{
}

Deck* HexusOpponentData::getDeck()
{
	return Deck::create(this->cardStyle, this->cards);
}

CardData* HexusOpponentData::getStrongestCard()
{
	CardData* best = nullptr;

	for (auto it = this->cards.begin(); it != this->cards.end(); it++)
	{
		if (best == nullptr || (*it)->attack > best->attack)
		{
			best = *it;
		}
	}

	return best;
}

int HexusOpponentData::generateReward(float deckStrength)
{
	float strengthPercent = deckStrength * 100.0f;
	int adjusted = (strengthPercent * strengthPercent) / 10 + 15;

	return adjusted;
}

std::vector<CardData*> HexusOpponentData::generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards)
{
	deckSize = MathUtils::clamp(deckSize, 20, 60);
	deckStrength = MathUtils::clamp(deckStrength, 0.0f, 1.0f);

	// Formula: Best possible generated card attack = (DeckStrength + 10%) * 15
	int maxGeneratedDeckCardAttack = MathUtils::clamp((int)((deckStrength + 0.1f) * 15), 0, 15);

	std::vector<CardData*> deck = std::vector<CardData*>();

	for (auto it = guaranteedCards.begin(); it != guaranteedCards.end(); it++)
	{
		deck.push_back(*it);
		deckSize--;
	}

	// Adjust deck strength via a "quadratic easeOut" function -- solves issues of not being able to properly fill the deck
	// ie) If the best deck for a size 21 deck is 300, and deckStrength is 10%, we would expect a deck of 30 strength, but this is impossible with 21 cards.
	// My assumption is that this will be OK -- it makes lower % decks a bit stronger, and higher % decks a bit weaker, however I think that
	// these imbalances can be made up with intelligently distributed special cards
	float adjustedDeckStrength = MathUtils::clamp(deckStrength * (2.0f - deckStrength), 0.0f, 1.0f);

	// Calculate the total attack this deck should have
	int generatedDeckAttack = HexusOpponentData::getBestPossibleDeckAttack(deckSize) * adjustedDeckStrength;

	std::vector<int> possibleCards = std::vector<int>();

	for (int attack = maxGeneratedDeckCardAttack; attack > 0; attack--)
	{
		for (int cardType = 0; cardType < 3; cardType++)
		{
			for (int repeatCard = 0; repeatCard < 3; repeatCard++)
			{
				possibleCards.push_back(attack);
			}
		}
	}

	// TODO: Possible cards should take into account guaranteed cards -- not a huge deal but currently this can result in more than 3 cards of the same type

	std::vector<int> deckCards = AlgoUtils::subsetSum(possibleCards, generatedDeckAttack, deckSize);
	std::map<int, int> addedCards = std::map<int, int>();

	for (auto it = deckCards.begin(); it != deckCards.end(); it++)
	{
		if (addedCards.find(*it) == addedCards.end())
		{
			// Start zero-indexed counter
			addedCards.emplace(*it, 0);
		}
		else
		{
			addedCards[*it] = addedCards[*it] + 1;
		}

		// Alternate between adding bin/hex/dec for cards of the same attack to keep decks diverse
		switch (addedCards[*it] % 3)
		{
			// Binary is 1st priority
			default:
			case 0:
				deck.push_back(HexusOpponentData::getBinaryCardForAttack(*it));
				break;
				// Prioritize hex next
			case 1:
				deck.push_back(HexusOpponentData::getHexCardForAttack(*it));
				break;
				// Finally decimal
			case 2:
				deck.push_back(HexusOpponentData::getDecimalCardForAttack(*it));
				break;
		}
	}

	return deck;
}

int HexusOpponentData::getBestPossibleDeckAttack(int deckSize)
{
	int bestDeckAttack = 0;
	int repeatedCardCount = 0;

	// For all attack values
	for (int nextAttack = 15; nextAttack > 0; nextAttack--)
	{
		// For all types (bin/dec/hex)
		for (int cardTypeIndex = 0; cardTypeIndex < 3; cardTypeIndex++)
		{
			// For the maximum amount of duplicated cards (3)
			for (int repeatedCount = 0; repeatedCount < 3; repeatedCount++)
			{
				bestDeckAttack += nextAttack;
				deckSize--;

				if (deckSize == 0)
				{
					return bestDeckAttack;
				}
			}
		}
	}

	return bestDeckAttack;
}


CardData* HexusOpponentData::getBinaryCardForAttack(int attack)
{
	attack = MathUtils::clamp(attack, 0, 15);

	switch (attack)
	{
		case 0:
		default:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary0);
		case 1:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary1);
		case 2:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary2);
		case 3:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary3);
		case 4:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary4);
		case 5:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary5);
		case 6:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary6);
		case 7:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary7);
		case 8:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary8);
		case 9:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary9);
		case 10:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary10);
		case 11:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary11);
		case 12:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary12);
		case 13:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary13);
		case 14:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary14);
		case 15:
			return CardList::getInstance()->cardListByName->at(CardKeys::Binary15);
	}
}

CardData* HexusOpponentData::getDecimalCardForAttack(int attack)
{
	attack = MathUtils::clamp(attack, 0, 15);

	switch (attack)
	{
		case 0:
		default:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal0);
		case 1:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal1);
		case 2:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal2);
		case 3:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal3);
		case 4:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal4);
		case 5:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal5);
		case 6:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal6);
		case 7:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal7);
		case 8:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal8);
		case 9:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal9);
		case 10:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal10);
		case 11:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal11);
		case 12:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal12);
		case 13:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal13);
		case 14:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal14);
		case 15:
			return CardList::getInstance()->cardListByName->at(CardKeys::Decimal15);
	}
}

CardData* HexusOpponentData::getHexCardForAttack(int attack)
{
	attack = MathUtils::clamp(attack, 0, 15);

	switch (attack)
	{
		case 0:
		default:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex0);
		case 1:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex1);
		case 2:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex2);
		case 3:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex3);
		case 4:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex4);
		case 5:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex5);
		case 6:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex6);
		case 7:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex7);
		case 8:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex8);
		case 9:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex9);
		case 10:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex10);
		case 11:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex11);
		case 12:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex12);
		case 13:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex13);
		case 14:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex14);
		case 15:
			return CardList::getInstance()->cardListByName->at(CardKeys::Hex15);
	}
}
