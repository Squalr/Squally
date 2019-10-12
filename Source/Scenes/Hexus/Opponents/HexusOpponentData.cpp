#include "HexusOpponentData.h"

#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/StateOverride.h"

using namespace cocos2d;

const std::string HexusOpponentData::winsPrefix = "WINS_";
const std::string HexusOpponentData::lossesPrefix = "LOSSES_";

HexusOpponentData* HexusOpponentData::create(
	std::string animationResourceFile,
	std::string backgroundResourceFile,
	float animationScale,
	Vec2 animationOffset,
	Vec2 frameOffset,
	Vec2 avatarOffset,
	std::string enemyNameKey,
	HexusOpponentData::Strategy strategy,
	Card::CardStyle cardStyle,
	float strength,
	std::vector<CardData*> cards,
	ItemPool* rewardPool,
	std::function<void(Result)> onRoundEnd,
	StateOverride* stateOverride)
{
	HexusOpponentData* instance = new HexusOpponentData(
		animationResourceFile,
		backgroundResourceFile,
		animationScale,
		animationOffset,
		frameOffset,
		avatarOffset,
		enemyNameKey,
		strategy,
		cardStyle,
		strength,
		cards,
		rewardPool,
		onRoundEnd,
		stateOverride
	);

	instance->autorelease();

	return instance;
}

HexusOpponentData::HexusOpponentData(
	std::string animationResourceFile,
	std::string backgroundResourceFile,
	float animationScale,
	Vec2 animationOffset,
	Vec2 frameOffset,
	Vec2 avatarOffset,
	std::string enemyNameKey,
	HexusOpponentData::Strategy strategy,
	Card::CardStyle cardStyle,
	float strength,
	std::vector<CardData*> cards,
	ItemPool* rewardPool,
	std::function<void(Result)> onRoundEnd,
	StateOverride* stateOverride)
{
	this->animationResourceFile = animationResourceFile;
	this->backgroundResourceFile = backgroundResourceFile;
	this->animationScale = animationScale;
	this->animationOffset = animationOffset;
	this->frameOffset = frameOffset;
	this->avatarOffset = avatarOffset;
	this->enemyNameKey = enemyNameKey;
	this->strategy = strategy;
	this->cardStyle = cardStyle;
	this->strength = strength;
	this->reward = HexusOpponentData::generateReward(this->strength);
	this->cards = cards;
	this->onRoundEnd = onRoundEnd;
	this->rewardPool = rewardPool;
	this->stateOverride = stateOverride;
	this->isLastInChapter = false;

	if (this->stateOverride != nullptr)
	{
		this->stateOverride->retain();
	}

	this->addChild(this->rewardPool);
}

HexusOpponentData::~HexusOpponentData()
{
	if (this->stateOverride != nullptr)
	{
		this->stateOverride->release();
	}
}

Deck* HexusOpponentData::getDeck()
{
	return Deck::create(this->cardStyle, this->cards, false);
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
	// This should give us a distribution where the mininum is 32 (easiest opponent) the maximum is 512 (hardest opponent), with a healthy weight to early opponents
	// Formula: Lagrange interpolation over (0.0, 32), (0.3, 240), (1.0, 512)
	const float alpha = -304.762f;
	const float beta = 785.762f;
	const float gamma = 32.0f;

	int adjusted = int((deckStrength * deckStrength) * alpha + (deckStrength * beta) + gamma);

	return MathUtils::clamp(adjusted, 0, 512);
}

std::vector<CardData*> HexusOpponentData::generateDeck(int deckSize, float deckStrength, std::vector<CardData*> guaranteedCards)
{
	deckSize = MathUtils::clamp(deckSize, 20, 60);
	deckStrength = MathUtils::clamp(deckStrength, 0.0f, 1.0f);

	// Formula: Best possible card attack for a single card = (DeckStrength + 10%) * 15 (min: 3)
	int maxGeneratedDeckCardAttack = MathUtils::clamp((int)std::ceil((deckStrength + 0.10f) * 15), 2, 15);

	std::vector<CardData*> deck = std::vector<CardData*>();

	// Always guarantee 0 cards, this seems to actually make for solid gameplay :)
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Binary0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Binary0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Binary0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Decimal0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Decimal0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Decimal0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Hex0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Hex0]);
	guaranteedCards.push_back(CardList::getInstance()->cardListByName[CardKeys::Hex0]);

	for (auto it = guaranteedCards.begin(); it != guaranteedCards.end(); it++)
	{
		deck.push_back(*it);
		deckSize--;
	}

	// Map the space [0.0, 1.0] to [0.10, 1.0]. There are some decks too weak to exist, this solves that problem.
	const float lowestNewStrength = 0.10f;
	float adjustedDeckStrength = MathUtils::clamp(lowestNewStrength + (1.0f - lowestNewStrength) * deckStrength, 0.0f, 1.0f);

	// Calculate the total attack this deck should have
	int generatedDeckAttack = int(std::ceil(float(HexusOpponentData::getBestPossibleDeckAttack(deckSize)) * adjustedDeckStrength));

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
	
	std::vector<int> deckCards = AlgoUtils::subsetSum(possibleCards, generatedDeckAttack, deckSize);
	std::map<int, int> addedCards = std::map<int, int>();

	for (auto it = deckCards.begin(); it != deckCards.end(); it++)
	{
		int attack = *it;

		if (addedCards.find(attack) == addedCards.end())
		{
			// Start zero-indexed counter
			addedCards[attack] = 0;
		}
		else
		{
			addedCards[attack] = addedCards[attack] + 1;
		}

		if (attack != 1)
		{
			// Alternate between adding bin/hex/dec for cards of the same attack to keep decks diverse
			switch (addedCards[attack] % 3)
			{
				// Binary is 1st priority
				default:
				case 0:
				{
					deck.push_back(HexusOpponentData::getBinaryCardForAttack(attack));
					break;
				}
				// Prioritize hex next
				case 1:
				{
					deck.push_back(HexusOpponentData::getHexCardForAttack(attack));
					break;
				}
				// Finally decimal
				case 2:
				{
					deck.push_back(HexusOpponentData::getDecimalCardForAttack(attack));
					break;
				}
			}
		}
		else
		{
			// Special logic for 1 cards! We want to prioritize maxing out 'horde spiders' and 'scared girl'
			switch (addedCards[attack] / 3)
			{
				// Hex is 1st priority
				default:
				case 0:
				{
					deck.push_back(HexusOpponentData::getHexCardForAttack(attack));
					break;
				}
				// Dec hex next
				case 1:
				{
					deck.push_back(HexusOpponentData::getDecimalCardForAttack(attack));
					break;
				}
				// Finally decimal
				case 2:
				{
					deck.push_back(HexusOpponentData::getBinaryCardForAttack(attack));
					break;
				}
			}
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
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary0);
		}
		case 1:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary1);
		}
		case 2:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary2);
		}
		case 3:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary3);
		}
		case 4:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary4);
		}
		case 5:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary5);
		}
		case 6:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary6);
		}
		case 7:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary7);
		}
		case 8:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary8);
		}
		case 9:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary9);
		}
		case 10:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary10);
		}
		case 11:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary11);
		}
		case 12:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary12);
		}
		case 13:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary13);
		}
		case 14:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary14);
		}
		case 15:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Binary15);
		}
	}
}

CardData* HexusOpponentData::getDecimalCardForAttack(int attack)
{
	attack = MathUtils::clamp(attack, 0, 15);

	switch (attack)
	{
		case 0:
		default:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal0);
		}
		case 1:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal1);
		}
		case 2:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal2);
		}
		case 3:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal3);
		}
		case 4:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal4);
		}
		case 5:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal5);
		}
		case 6:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal6);
		}
		case 7:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal7);
		}
		case 8:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal8);
		}
		case 9:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal9);
		}
		case 10:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal10);
		}
		case 11:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal11);
		}
		case 12:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal12);
		}
		case 13:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal13);
		}
		case 14:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal14);
		}
		case 15:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Decimal15);
		}
	}
}

CardData* HexusOpponentData::getHexCardForAttack(int attack)
{
	attack = MathUtils::clamp(attack, 0, 15);

	switch (attack)
	{
		case 0:
		default:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex0);
		}
		case 1:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex1);
		}
		case 2:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex2);
		}
		case 3:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex3);
		}
		case 4:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex4);
		}
		case 5:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex5);
		}
		case 6:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex6);
		}
		case 7:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex7);
		}
		case 8:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex8);
		}
		case 9:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex9);
		}
		case 10:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex10);
		}
		case 11:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex11);
		}
		case 12:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex12);
		}
		case 13:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex13);
		}
		case 14:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex14);
		}
		case 15:
		{
			return CardList::getInstance()->cardListByName.at(CardKeys::Hex15);
		}
	}
}

void HexusOpponentData::setIsLastInChapter()
{
	this->isLastInChapter = true;
}

bool HexusOpponentData::getIsLastInChapter()
{
	return this->isLastInChapter;
}
