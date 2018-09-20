#pragma once
#include "cocos2d.h"

#include "Resources.h"
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
#include "Scenes/Hexus/CardData/Special/CardAddition.h"
#include "Scenes/Hexus/CardData/Special/CardEnvironmentBinStorm.h"
#include "Scenes/Hexus/CardData/Special/CardEnvironmentDecStorm.h"
#include "Scenes/Hexus/CardData/Special/CardEnvironmentHexStorm.h"
#include "Scenes/Hexus/CardData/Special/CardFlip1.h"
#include "Scenes/Hexus/CardData/Special/CardFlip2.h"
#include "Scenes/Hexus/CardData/Special/CardFlip3.h"
#include "Scenes/Hexus/CardData/Special/CardFlip4.h"
#include "Scenes/Hexus/CardData/Special/CardInverse.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalAnd.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalOr.h"
#include "Scenes/Hexus/CardData/Special/CardLogicalXor.h"
#include "Scenes/Hexus/CardData/Special/CardShiftLeft.h"
#include "Scenes/Hexus/CardData/Special/CardShiftRight.h"
#include "Scenes/Hexus/CardData/Special/CardSubtraction.h"

using namespace cocos2d;

class CardList
{
public:
	static CardList* getInstance();

	static const std::string Binary0;
	static const std::string Binary1;
	static const std::string Binary2;
	static const std::string Binary3;
	static const std::string Binary4;
	static const std::string Binary5;
	static const std::string Binary6;
	static const std::string Binary7;
	static const std::string Binary8;
	static const std::string Binary9;
	static const std::string Binary10;
	static const std::string Binary11;
	static const std::string Binary12;
	static const std::string Binary13;
	static const std::string Binary14;
	static const std::string Binary15;
	static const std::string Decimal0;
	static const std::string Decimal1;
	static const std::string Decimal2;
	static const std::string Decimal3;
	static const std::string Decimal4;
	static const std::string Decimal5;
	static const std::string Decimal6;
	static const std::string Decimal7;
	static const std::string Decimal8;
	static const std::string Decimal9;
	static const std::string Decimal10;
	static const std::string Decimal11;
	static const std::string Decimal12;
	static const std::string Decimal13;
	static const std::string Decimal14;
	static const std::string Decimal15;
	static const std::string Hex0;
	static const std::string Hex1;
	static const std::string Hex2;
	static const std::string Hex3;
	static const std::string Hex4;
	static const std::string Hex5;
	static const std::string Hex6;
	static const std::string Hex7;
	static const std::string Hex8;
	static const std::string Hex9;
	static const std::string Hex10;
	static const std::string Hex11;
	static const std::string Hex12;
	static const std::string Hex13;
	static const std::string Hex14;
	static const std::string Hex15;
	static const std::string Addition;
	static const std::string EnvironmentBinStorm;
	static const std::string EnvironmentClear;
	static const std::string EnvironmentDecStorm;
	static const std::string EnvironmentHexStorm;
	static const std::string Flip1;
	static const std::string Flip2;
	static const std::string Flip3;
	static const std::string Flip4;
	static const std::string Inverse;
	static const std::string LogicalAnd;
	static const std::string LogicalOr;
	static const std::string LogicalXor;
	static const std::string ShiftLeft;
	static const std::string ShiftRight;
	static const std::string Subtraction;

	std::map<std::string, CardData*>* cardListByName;
	
protected:
	CardList();
	~CardList();

private:

	static CardList* instance;
};

