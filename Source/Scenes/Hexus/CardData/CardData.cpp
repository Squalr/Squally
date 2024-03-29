#include "CardData.h"

#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Strings/Strings.h"

CardData::CardData(std::string cardResourceFile, std::string cardKey, CardType cardType, unsigned int attack)
{
	this->cardResourceFile = cardResourceFile;
	this->cardKey = cardKey;
	this->cardType = cardType;
	this->attack = attack;
}

CardData::~CardData()
{
}

std::string CardData::getCardResourceFile()
{
	return this->cardResourceFile;
}

std::string CardData::getCardKey()
{
	return this->cardKey;
}

CardData::CardType CardData::getCardType()
{
	return this->cardType;
}

unsigned int CardData::getAttack()
{
	return this->attack;
}

LocalizedString* CardData::getCardTypeString()
{
	switch (this->cardType)
	{
		case CardData::CardType::Binary:
		{
			return Strings::Hexus_Cards_Abbreviations_BIN::create();
		}
		case CardData::CardType::Decimal:
		{
			return Strings::Hexus_Cards_Abbreviations_DEC::create();
		}
		case CardData::CardType::Hexidecimal:
		{
			return Strings::Hexus_Cards_Abbreviations_HEX::create();
		}
		case CardData::CardType::Special_MOV:
		{
			return Strings::Hexus_Cards_Abbreviations_MOV::create();
		}
		case CardData::CardType::Special_AND:
		{
			return Strings::Hexus_Cards_Abbreviations_AND::create();
		}
		case CardData::CardType::Special_OR:
		{
			return Strings::Hexus_Cards_Abbreviations_OR::create();
		}
		case CardData::CardType::Special_XOR:
		{
			return Strings::Hexus_Cards_Abbreviations_XOR::create();
		}
		case CardData::CardType::Special_SHL:
		{
			return Strings::Hexus_Cards_Abbreviations_SHL::create();
		}
		case CardData::CardType::Special_SHR:
		{
			return Strings::Hexus_Cards_Abbreviations_SHR::create();
		}
		case CardData::CardType::Special_ROL:
		{
			return Strings::Hexus_Cards_Abbreviations_ROL::create();
		}
		case CardData::CardType::Special_ROR:
		{
			return Strings::Hexus_Cards_Abbreviations_ROR::create();
		}
		case CardData::CardType::Special_NOT:
		{
			return Strings::Hexus_Cards_Abbreviations_NOT::create();
		}
		case CardData::CardType::Special_CLEAR:
		{
			return Strings::Common_Empty::create();
		}
		case CardData::CardType::Special_PEEK:
		{
			return Strings::Hexus_Cards_Abbreviations_Peek::create();
		}
		case CardData::CardType::Special_FLIP1:
		{
			return Strings::Hexus_Cards_Abbreviations_FLIP1::create();
		}
		case CardData::CardType::Special_FLIP2:
		{
			return Strings::Hexus_Cards_Abbreviations_FLIP2::create();
		}
		case CardData::CardType::Special_FLIP3:
		{
			return Strings::Hexus_Cards_Abbreviations_FLIP3::create();
		}
		case CardData::CardType::Special_FLIP4:
		{
			return Strings::Hexus_Cards_Abbreviations_FLIP4::create();
		}
		case CardData::CardType::Special_ADD:
		{
			return Strings::Hexus_Cards_Abbreviations_ADD::create();
		}
		case CardData::CardType::Special_SUB:
		{
			return Strings::Hexus_Cards_Abbreviations_SUB::create();
		}
		case CardData::CardType::Special_PUSH:
		{
			return Strings::Hexus_Cards_Abbreviations_PUSH::create();
		}
		case CardData::CardType::Special_POP:
		{
			return Strings::Hexus_Cards_Abbreviations_POP::create();
		}
		case CardData::CardType::Special_SUDDEN_DEATH:
		case CardData::CardType::Special_GREED:
		case CardData::CardType::Special_ABSORB:
		case CardData::CardType::Special_RETURN_TO_HAND:
		case CardData::CardType::Special_STEAL:
		case CardData::CardType::Special_BONUS_MOVES:
		{
			return Strings::Common_Empty::create();
		}
		default:
		{
			return Strings::Hexus_Cards_Abbreviations_ERR::create();
		}
	}
}

LocalizedString* CardData::getCardOperationString()
{
	switch (this->cardType)
	{
		case CardData::CardType::Special_MOV:
		{
			return Strings::Hexus_Cards_Abbreviations_MOV::create();
		}
		case CardData::CardType::Special_AND:
		{
			return Strings::Hexus_Cards_Abbreviations_AND::create();
		}
		case CardData::CardType::Special_OR:
		{
			return Strings::Hexus_Cards_Abbreviations_OR::create();
		}
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			return Strings::Hexus_Cards_Abbreviations_XOR::create();
		}
		case CardData::CardType::Special_SHL:
		{
			return Strings::Hexus_Cards_Abbreviations_SHL::create();
		}
		case CardData::CardType::Special_SHR:
		{
			return Strings::Hexus_Cards_Abbreviations_SHR::create();
		}
		case CardData::CardType::Special_ROL:
		{
			return Strings::Hexus_Cards_Abbreviations_ROL::create();
		}
		case CardData::CardType::Special_ROR:
		{
			return Strings::Hexus_Cards_Abbreviations_ROR::create();
		}
		case CardData::CardType::Special_NOT:
		{
			return Strings::Hexus_Cards_Abbreviations_NOT::create();
		}
		case CardData::CardType::Special_CLEAR:
		{
			return Strings::Common_Empty::create();
		}
		case CardData::CardType::Special_ADD:
		{
			return Strings::Hexus_Cards_Abbreviations_ADD::create();
		}
		case CardData::CardType::Special_SUB:
		{
			return Strings::Hexus_Cards_Abbreviations_SUB::create();
		}
		case CardData::CardType::Binary:
		case CardData::CardType::Decimal:
		case CardData::CardType::Hexidecimal:
		case CardData::CardType::Special_SUDDEN_DEATH:
		case CardData::CardType::Special_GREED:
		case CardData::CardType::Special_ABSORB:
		case CardData::CardType::Special_PUSH:
		case CardData::CardType::Special_POP:
		case CardData::CardType::Special_RETURN_TO_HAND:
		case CardData::CardType::Special_STEAL:
		case CardData::CardType::Special_BONUS_MOVES:
		case CardData::CardType::Special_PEEK:
		default:
		{
			return Strings::Common_Empty::create();
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
		case CardData::CardType::Special_ABSORB:
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

bool CardData::isMultiTargetCard()
{
	switch (this->cardType)
	{
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

bool CardData::isFixedImmediateCard()
{
	switch (this->cardType)
	{
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_ROL:
		case CardData::CardType::Special_ROR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

unsigned int CardData::getIntrinsicImmediate()
{
	switch (this->cardType)
	{
		case CardData::CardType::Binary:
		case CardData::CardType::Decimal:
		case CardData::CardType::Hexidecimal:
		case CardData::CardType::Special_SUDDEN_DEATH:
		{
			return this->attack;
		}
		case CardData::CardType::Special_BONUS_MOVES:
		{
			return 3;
		}
		case CardData::CardType::Special_FLIP1:
		{
			return 0b0001;
		}
		case CardData::CardType::Special_FLIP2:
		{
			return 0b0010;
		}
		case CardData::CardType::Special_FLIP3:
		{
			return 0b0100;
		}
		case CardData::CardType::Special_FLIP4:
		{
			return 0b1000;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_ROR:
		case CardData::CardType::Special_ROL:
		{
			return 0b0001;
		}
		case CardData::CardType::Special_MOV:
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_NOT:
		case CardData::CardType::Special_CLEAR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
		case CardData::CardType::Special_GREED:
		case CardData::CardType::Special_ABSORB:
		case CardData::CardType::Special_PUSH:
		case CardData::CardType::Special_POP:
		case CardData::CardType::Special_RETURN_TO_HAND:
		case CardData::CardType::Special_STEAL:
		case CardData::CardType::Special_PEEK:
		default:
		{
			return 0;
		}
	}
}
