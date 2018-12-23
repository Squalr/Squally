#include "CardData.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

CardData::CardData(std::string newCardResourceFile, std::string newCardName, CardType newCardType, unsigned int newAttack)
{
	this->cardResourceFile = newCardResourceFile;
	this->cardName = newCardName;
	this->cardType = newCardType;
	this->attack = newAttack;
}

CardData::~CardData()
{
}

std::string CardData::getCardTypeString()
{
	switch (this->cardType)
	{
		case CardData::CardType::Binary:
		{
			return "BIN";
		}
		case CardData::CardType::Decimal:
		{
			return "DEC";
		}
		case CardData::CardType::Hexidecimal:
		{
			return "HEX";
		}
		case CardData::CardType::Special_MOV:
		{
			return "MOV";
		}
		case CardData::CardType::Special_AND:
		{
			return "AND";
		}
		case CardData::CardType::Special_OR:
		{
			return "OR";
		}
		case CardData::CardType::Special_XOR:
		{
			return "XOR";
		}
		case CardData::CardType::Special_SHL:
		{
			return "SHL";
		}
		case CardData::CardType::Special_SHR:
		{
			return "SHR";
		}
		case CardData::CardType::Special_INV:
		{
			return "INV";
		}
		case CardData::CardType::Special_FLIP1:
		{
			return "FLIP1";
		}
		case CardData::CardType::Special_FLIP2:
		{
			return "FLIP2";
		}
		case CardData::CardType::Special_FLIP3:
		{
			return "FLIP3";
		}
		case CardData::CardType::Special_FLIP4:
		{
			return "FLIP4";
		}
		case CardData::CardType::Special_ADD:
		{
			return "ADD";
		}
		case CardData::CardType::Special_SUB:
		{
			return "SUB";
		}
		default:
		{
			return "ERR";
		}
	}
}

bool CardData::isAttackCard()
{
	switch (this->cardType)
	{
		case CardData::CardType::Binary:
		case CardData::CardType::Decimal:
		case CardData::CardType::Hexidecimal:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

bool CardData::isSpecialCard()
{
	return !this->isAttackCard();
}
