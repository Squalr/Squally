#include "CardList.h"
#include <algorithm>

#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary0.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary1.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary2.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary3.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary4.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary5.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary6.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary7.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary8.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary9.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary10.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary11.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary12.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary13.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary14.h"
#include "Scenes/Hexus/CardData/Binary/CardBinary15.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal0.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal1.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal2.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal3.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal4.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal5.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal6.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal7.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal8.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal9.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal10.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal11.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal12.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal13.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal14.h"
#include "Scenes/Hexus/CardData/Decimal/CardDecimal15.h"
#include "Scenes/Hexus/CardData/Hex/CardHex0.h"
#include "Scenes/Hexus/CardData/Hex/CardHex1.h"
#include "Scenes/Hexus/CardData/Hex/CardHex2.h"
#include "Scenes/Hexus/CardData/Hex/CardHex3.h"
#include "Scenes/Hexus/CardData/Hex/CardHex4.h"
#include "Scenes/Hexus/CardData/Hex/CardHex5.h"
#include "Scenes/Hexus/CardData/Hex/CardHex6.h"
#include "Scenes/Hexus/CardData/Hex/CardHex7.h"
#include "Scenes/Hexus/CardData/Hex/CardHex8.h"
#include "Scenes/Hexus/CardData/Hex/CardHex9.h"
#include "Scenes/Hexus/CardData/Hex/CardHex10.h"
#include "Scenes/Hexus/CardData/Hex/CardHex11.h"
#include "Scenes/Hexus/CardData/Hex/CardHex12.h"
#include "Scenes/Hexus/CardData/Hex/CardHex13.h"
#include "Scenes/Hexus/CardData/Hex/CardHex14.h"
#include "Scenes/Hexus/CardData/Hex/CardHex15.h"
#include "Scenes/Hexus/CardData/Special/CardAbsorb.h"
#include "Scenes/Hexus/CardData/Special/CardAddition.h"
#include "Scenes/Hexus/CardData/Special/CardBonusMoves.h"
#include "Scenes/Hexus/CardData/Special/CardClear.h"
#include "Scenes/Hexus/CardData/Special/CardDrank.h"
#include "Scenes/Hexus/CardData/Special/CardFlip1.h"
#include "Scenes/Hexus/CardData/Special/CardFlip2.h"
#include "Scenes/Hexus/CardData/Special/CardFlip3.h"
#include "Scenes/Hexus/CardData/Special/CardFlip4.h"
#include "Scenes/Hexus/CardData/Special/CardGreed.h"
#include "Scenes/Hexus/CardData/Special/CardHeal.h"
#include "Scenes/Hexus/CardData/Special/CardHibernate.h"
#include "Scenes/Hexus/CardData/Special/CardInverse.h"
#include "Scenes/Hexus/CardData/Special/CardKill.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalAnd.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalOr.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalXor.h"
#include "Scenes/Hexus/CardData/Special/CardMov.h"
#include "Scenes/Hexus/CardData/Special/CardPeek.h"
#include "Scenes/Hexus/CardData/Special/CardPoison.h"
#include "Scenes/Hexus/CardData/Special/CardProtect.h"
#include "Scenes/Hexus/CardData/Special/CardResurrect.h"
#include "Scenes/Hexus/CardData/Special/CardReturnToHand.h"
#include "Scenes/Hexus/CardData/Special/CardShiftLeft.h"
#include "Scenes/Hexus/CardData/Special/CardShiftRight.h"
#include "Scenes/Hexus/CardData/Special/CardSteal.h"
#include "Scenes/Hexus/CardData/Special/CardSubtraction.h"
#include "Scenes/Hexus/CardData/Special/CardSuddenDeath.h"

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
	this->cardListByName = std::map<std::string, CardData*>();
	this->sortedCardList = std::vector<CardData*>();

	this->cardListByName[CardKeys::Binary0] = new CardBinary0();
	this->cardListByName[CardKeys::Binary1] = new CardBinary1();
	this->cardListByName[CardKeys::Binary2] = new CardBinary2();
	this->cardListByName[CardKeys::Binary3] = new CardBinary3();
	this->cardListByName[CardKeys::Binary4] = new CardBinary4();
	this->cardListByName[CardKeys::Binary5] = new CardBinary5();
	this->cardListByName[CardKeys::Binary6] = new CardBinary6();
	this->cardListByName[CardKeys::Binary7] = new CardBinary7();
	this->cardListByName[CardKeys::Binary8] = new CardBinary8();
	this->cardListByName[CardKeys::Binary9] = new CardBinary9();
	this->cardListByName[CardKeys::Binary10] = new CardBinary10();
	this->cardListByName[CardKeys::Binary11] = new CardBinary11();
	this->cardListByName[CardKeys::Binary12] = new CardBinary12();
	this->cardListByName[CardKeys::Binary13] = new CardBinary13();
	this->cardListByName[CardKeys::Binary14] = new CardBinary14();
	this->cardListByName[CardKeys::Binary15] = new CardBinary15();
	this->cardListByName[CardKeys::Binary15] = new CardBinary15();

	this->cardListByName[CardKeys::Decimal0] = new CardDecimal0();
	this->cardListByName[CardKeys::Decimal1] = new CardDecimal1();
	this->cardListByName[CardKeys::Decimal2] = new CardDecimal2();
	this->cardListByName[CardKeys::Decimal3] = new CardDecimal3();
	this->cardListByName[CardKeys::Decimal4] = new CardDecimal4();
	this->cardListByName[CardKeys::Decimal5] = new CardDecimal5();
	this->cardListByName[CardKeys::Decimal6] = new CardDecimal6();
	this->cardListByName[CardKeys::Decimal7] = new CardDecimal7();
	this->cardListByName[CardKeys::Decimal8] = new CardDecimal8();
	this->cardListByName[CardKeys::Decimal9] = new CardDecimal9();
	this->cardListByName[CardKeys::Decimal10] = new CardDecimal10();
	this->cardListByName[CardKeys::Decimal11] = new CardDecimal11();
	this->cardListByName[CardKeys::Decimal12] = new CardDecimal12();
	this->cardListByName[CardKeys::Decimal13] = new CardDecimal13();
	this->cardListByName[CardKeys::Decimal14] = new CardDecimal14();
	this->cardListByName[CardKeys::Decimal15] = new CardDecimal15();

	this->cardListByName[CardKeys::Hex0] = new CardHex0();
	this->cardListByName[CardKeys::Hex1] = new CardHex1();
	this->cardListByName[CardKeys::Hex2] = new CardHex2();
	this->cardListByName[CardKeys::Hex3] = new CardHex3();
	this->cardListByName[CardKeys::Hex4] = new CardHex4();
	this->cardListByName[CardKeys::Hex5] = new CardHex5();
	this->cardListByName[CardKeys::Hex6] = new CardHex6();
	this->cardListByName[CardKeys::Hex7] = new CardHex7();
	this->cardListByName[CardKeys::Hex8] = new CardHex8();
	this->cardListByName[CardKeys::Hex9] = new CardHex9();
	this->cardListByName[CardKeys::Hex10] = new CardHex10();
	this->cardListByName[CardKeys::Hex11] = new CardHex11();
	this->cardListByName[CardKeys::Hex12] = new CardHex12();
	this->cardListByName[CardKeys::Hex13] = new CardHex13();
	this->cardListByName[CardKeys::Hex14] = new CardHex14();
	this->cardListByName[CardKeys::Hex15] = new CardHex15();

	this->cardListByName[CardKeys::Addition] = new CardAddition();
	this->cardListByName[CardKeys::Flip1] = new CardFlip1();
	this->cardListByName[CardKeys::Flip2] = new CardFlip2();
	this->cardListByName[CardKeys::Flip3] = new CardFlip3();
	this->cardListByName[CardKeys::Flip4] = new CardFlip4();
	this->cardListByName[CardKeys::Inverse] = new CardInverse();
	this->cardListByName[CardKeys::LogicalAnd] = new CardLogicalAnd();
	this->cardListByName[CardKeys::LogicalOr] = new CardLogicalOr();
	this->cardListByName[CardKeys::LogicalXor] = new CardLogicalXor();
	this->cardListByName[CardKeys::Mov] = new CardMov();
	this->cardListByName[CardKeys::ShiftLeft] = new CardShiftLeft();
	this->cardListByName[CardKeys::ShiftRight] = new CardShiftRight();
	this->cardListByName[CardKeys::Subtraction] = new CardSubtraction();

	this->cardListByName[CardKeys::Absorb] = new CardAbsorb();
	this->cardListByName[CardKeys::BonusMoves] = new CardBonusMoves();
	this->cardListByName[CardKeys::Clear] = new CardClear();
	this->cardListByName[CardKeys::Drank] = new CardDrank();
	this->cardListByName[CardKeys::Greed] = new CardGreed();
	this->cardListByName[CardKeys::Heal] = new CardHeal();
	this->cardListByName[CardKeys::Hibernate] = new CardHibernate();
	this->cardListByName[CardKeys::Kill] = new CardKill();
	this->cardListByName[CardKeys::Peek] = new CardPeek();
	this->cardListByName[CardKeys::Poison] = new CardPoison();
	this->cardListByName[CardKeys::Protect] = new CardProtect();
	this->cardListByName[CardKeys::Resurrect] = new CardResurrect();
	this->cardListByName[CardKeys::ReturnToHand] = new CardReturnToHand();
	this->cardListByName[CardKeys::Steal] = new CardSteal();
	this->cardListByName[CardKeys::SuddenDeath] = new CardSuddenDeath();

	for (auto it = this->cardListByName.begin(); it != this->cardListByName.end(); it++)
	{
		this->sortedCardList.push_back((*it).second);
	}

	// Sort cards
	std::sort(this->sortedCardList.begin(), this->sortedCardList.end(), [](CardData* a, CardData* b) -> bool
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
			{
				// Sort by attack
				return a->attack < b->attack;
				break;
			}
			default:
			{
				// Sort by card type
				return a->cardType < b->cardType;
			}
		}
	});
}

CardList::~CardList()
{
	for (auto it = this->cardListByName.begin(); it != this->cardListByName.end(); it++)
	{
		delete(it->second);
	}
}
