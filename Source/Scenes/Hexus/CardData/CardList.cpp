#include "CardList.h"

CardList* CardList::instance = nullptr;

CardList* CardList::getInstance()
{
	if (CardList::instance == nullptr)
	{
		CardList::instance = new CardList();
	}

	return CardList::instance;
}

CardList::CardList()
{
	this->cardListByName = new std::map<std::string, CardData*>();
	this->sortedCardList = new std::vector<CardData*>();

	this->cardListByName->emplace(CardKeys::Binary0, new CardBinary0());
	this->cardListByName->emplace(CardKeys::Binary1, new CardBinary1());
	this->cardListByName->emplace(CardKeys::Binary2, new CardBinary2());
	this->cardListByName->emplace(CardKeys::Binary3, new CardBinary3());
	this->cardListByName->emplace(CardKeys::Binary4, new CardBinary4());
	this->cardListByName->emplace(CardKeys::Binary5, new CardBinary5());
	this->cardListByName->emplace(CardKeys::Binary6, new CardBinary6());
	this->cardListByName->emplace(CardKeys::Binary7, new CardBinary7());
	this->cardListByName->emplace(CardKeys::Binary8, new CardBinary8());
	this->cardListByName->emplace(CardKeys::Binary9, new CardBinary9());
	this->cardListByName->emplace(CardKeys::Binary10, new CardBinary10());
	this->cardListByName->emplace(CardKeys::Binary11, new CardBinary11());
	this->cardListByName->emplace(CardKeys::Binary12, new CardBinary12());
	this->cardListByName->emplace(CardKeys::Binary13, new CardBinary13());
	this->cardListByName->emplace(CardKeys::Binary14, new CardBinary14());
	this->cardListByName->emplace(CardKeys::Binary15, new CardBinary15());
	this->cardListByName->emplace(CardKeys::Binary15, new CardBinary15());

	this->cardListByName->emplace(CardKeys::Decimal0, new CardDecimal0());
	this->cardListByName->emplace(CardKeys::Decimal1, new CardDecimal1());
	this->cardListByName->emplace(CardKeys::Decimal2, new CardDecimal2());
	this->cardListByName->emplace(CardKeys::Decimal3, new CardDecimal3());
	this->cardListByName->emplace(CardKeys::Decimal4, new CardDecimal4());
	this->cardListByName->emplace(CardKeys::Decimal5, new CardDecimal5());
	this->cardListByName->emplace(CardKeys::Decimal6, new CardDecimal6());
	this->cardListByName->emplace(CardKeys::Decimal7, new CardDecimal7());
	this->cardListByName->emplace(CardKeys::Decimal8, new CardDecimal8());
	this->cardListByName->emplace(CardKeys::Decimal9, new CardDecimal9());
	this->cardListByName->emplace(CardKeys::Decimal10, new CardDecimal10());
	this->cardListByName->emplace(CardKeys::Decimal11, new CardDecimal11());
	this->cardListByName->emplace(CardKeys::Decimal12, new CardDecimal12());
	this->cardListByName->emplace(CardKeys::Decimal13, new CardDecimal13());
	this->cardListByName->emplace(CardKeys::Decimal14, new CardDecimal14());
	this->cardListByName->emplace(CardKeys::Decimal15, new CardDecimal15());

	this->cardListByName->emplace(CardKeys::Hex0, new CardHex0());
	this->cardListByName->emplace(CardKeys::Hex1, new CardHex1());
	this->cardListByName->emplace(CardKeys::Hex2, new CardHex2());
	this->cardListByName->emplace(CardKeys::Hex3, new CardHex3());
	this->cardListByName->emplace(CardKeys::Hex4, new CardHex4());
	this->cardListByName->emplace(CardKeys::Hex5, new CardHex5());
	this->cardListByName->emplace(CardKeys::Hex6, new CardHex6());
	this->cardListByName->emplace(CardKeys::Hex7, new CardHex7());
	this->cardListByName->emplace(CardKeys::Hex8, new CardHex8());
	this->cardListByName->emplace(CardKeys::Hex9, new CardHex9());
	this->cardListByName->emplace(CardKeys::Hex10, new CardHex10());
	this->cardListByName->emplace(CardKeys::Hex11, new CardHex11());
	this->cardListByName->emplace(CardKeys::Hex12, new CardHex12());
	this->cardListByName->emplace(CardKeys::Hex13, new CardHex13());
	this->cardListByName->emplace(CardKeys::Hex14, new CardHex14());
	this->cardListByName->emplace(CardKeys::Hex15, new CardHex15());

	this->cardListByName->emplace(CardKeys::Addition, new CardAddition());
	this->cardListByName->emplace(CardKeys::Flip1, new CardFlip1());
	this->cardListByName->emplace(CardKeys::Flip2, new CardFlip2());
	this->cardListByName->emplace(CardKeys::Flip3, new CardFlip3());
	this->cardListByName->emplace(CardKeys::Flip4, new CardFlip4());
	this->cardListByName->emplace(CardKeys::Inverse, new CardInverse());
	this->cardListByName->emplace(CardKeys::LogicalAnd, new CardLogicalAnd());
	this->cardListByName->emplace(CardKeys::LogicalOr, new CardLogicalOr());
	this->cardListByName->emplace(CardKeys::LogicalXor, new CardLogicalXor());
	this->cardListByName->emplace(CardKeys::ShiftLeft, new CardShiftLeft());
	this->cardListByName->emplace(CardKeys::ShiftRight, new CardShiftRight());
	this->cardListByName->emplace(CardKeys::Subtraction, new CardSubtraction());

	for (auto it = this->cardListByName->begin(); it != this->cardListByName->end(); it++)
	{
		this->sortedCardList->push_back((*it).second);
	}

	// Sort cards
	std::sort(this->sortedCardList->begin(), this->sortedCardList->end(), [](CardData* a, CardData* b) -> bool
	{
		// Non-matching types, just sort these by card type
		if (a->cardType != b->cardType)
		{
			return a->cardType < b->cardType;
		}

		switch (a->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
				// Sort by attack
				return a->attack < b->attack;
				break;
			default:
				// Sort by card type
				return a->cardType < b->cardType;
		}
	});
}

CardList::~CardList()
{
	for (auto it = this->cardListByName->begin(); it != this->cardListByName->end(); it++)
	{
		delete(it->second);
	}

	delete(this->cardListByName);
	delete(this->sortedCardList);
}
