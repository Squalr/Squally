#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class CardData
{
public:
	// Note: Hard code enum values to allow for future proofing if we ever remove an id
	enum CardType {
		Binary = 0,
		Decimal = 1,
		Hexidecimal = 2,
		Special_AND = 3,
		Special_OR = 4,
		Special_XOR = 5,
		Special_SHL = 6,
		Special_SHR = 7,
		Special_INV = 8,
		Special_FLIP1 = 9,
		Special_FLIP2 = 10,
		Special_FLIP3 = 11,
		Special_FLIP4 = 12,
		Special_ADD = 13,
		Special_SUB = 14,
		Special_ENV_CLEAR = 14,
		Special_ENV_BIN_STORM = 14,
		Special_ENV_DEC_STORM = 15,
		Special_ENV_HEX_STORM = 16,
	};

	CardData(std::string newCardResourceFile, std::string newCardName, CardType newCardType, unsigned int newAttack);
	~CardData();

	std::string getCardTypeString();

	std::string cardResourceFile;
	std::string cardName;
	CardType cardType;
	unsigned int attack;

private:
	std::map<int, CardData*> cardListById;
};

