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
		Special_NOT,
		Special_FLIP1,
		Special_FLIP2,
		Special_FLIP3,
		Special_FLIP4,
		Special_ADD,
		Special_SUB,
		Special_SUDDEN_DEATH,
		Special_GREED,
		Special_ABSORB,
		Special_KILL,
		Special_RETURN_TO_HAND,
		Special_STEAL,
		Special_BONUS_MOVES,
		Special_PEEK,
	};

	CardData(std::string cardResourceFile, std::string cardKey, CardType cardType, unsigned int attack);
	~CardData();

	LocalizedString* getCardTypeString();
	LocalizedString* getCardOperationString();
	bool isAttackCard();
	bool isSpecialCard();
	bool isMultiTargetCard();
	unsigned int getIntrinsicImmediate();

	std::string cardResourceFile;
	std::string cardKey;
	CardType cardType;
	unsigned int attack;
};
