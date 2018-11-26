#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

using namespace cocos2d;

class CardData
{
public:
	enum CardType {
		Binary,
		Decimal,
		Hexidecimal,
		Special_MOV,
		Special_AND,
		Special_OR,
		Special_XOR,
		Special_SHL,
		Special_SHR,
		Special_INV,
		Special_FLIP1,
		Special_FLIP2,
		Special_FLIP3,
		Special_FLIP4,
		Special_ADD,
		Special_SUB,
		Special_ENV_CLEAR,
		Special_ENV_BIN_STORM,
		Special_ENV_DEC_STORM,
		Special_ENV_HEX_STORM,
	};

	CardData(std::string newCardResourceFile, std::string newCardName, CardType newCardType, unsigned int newAttack);
	~CardData();

	std::string getCardTypeString();
	bool isAttackCard();
	bool isSpecialCard();

	std::string cardResourceFile;
	std::string cardName;
	CardType cardType;
	unsigned int attack;
};

