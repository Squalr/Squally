#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class CardData
{
public:
	static std::map<int, CardData*> cardList;

	enum CardType {
		Binary = 0,
		Decimal = 1,
		Hexidecimal = 2,
		Special = 3,
	};

private:
	CardData(std::string resourceFile, std::string cardName, CardType cardType);
	~CardData();
};

