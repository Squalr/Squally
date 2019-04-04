#pragma once
#include <string>

class LocalizedString;

class CardData
{
public:
	enum class CardType
	{
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
		Special_CLEAR,
		Special_SUDDEN_DEATH,
		Special_GREED,
		Special_ABSORB,
		Special_KILL,
		Special_RETURN_TO_HAND,
		Special_STEAL,
		Special_BONUS_MOVES,
		Special_PEEK,
		Special_HEAL,
		Special_POISON,
		Special_DRANK,
	};

	CardData(std::string cardResourceFile, std::string cardKey, CardType cardType, unsigned int attack);
	~CardData();

	LocalizedString* getCardTypeString();
	bool isAttackCard();
	bool isSpecialCard();
	bool isMultiTargetCard();
	unsigned int getIntrinsicImmediate();

	std::string cardResourceFile;
	std::string cardKey;
	CardType cardType;
	unsigned int attack;
};
