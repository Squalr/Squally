#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class HexusOpponent
{
public:
	std::string getCardTypeString();

	static std::map<std::string, HexusOpponent*> cardListByName;
	static std::map<int, HexusOpponent*> cardListById;

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
	};

	std::string cardResourceFile;
	std::string cardName;
	CardType cardType;
	unsigned int attack;

	static const std::string Kickstarter0;
	static const std::string Kickstarter1;
	static const std::string Kickstarter2;
	static const std::string Kickstarter3;
	static const std::string Kickstarter4;
	static const std::string Kickstarter5;
	static const std::string Kickstarter6;
	static const std::string Kickstarter7;
	static const std::string Kickstarter8;
	static const std::string Kickstarter9;
	static const std::string Kickstarter10;
	static const std::string Kickstarter11;
	static const std::string Kickstarter12;
	static const std::string Kickstarter13;
	static const std::string Kickstarter14;
	static const std::string Kickstarter15;
	static const std::string BossKrampus;

private:
	HexusOpponent(std::string animationResourceFile, std::string enemyName);
	~HexusOpponent();
};

