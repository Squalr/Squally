#pragma once
#include "cocos2d.h"

#include "Resources.h"
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
#include "Scenes/Hexus/CardData/Special/CardAddition.h"
#include "Scenes/Hexus/CardData/Special/CardEnvironmentBinStorm.h"
#include "Scenes/Hexus/CardData/Special/CardEnvironmentClear.h"
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

	std::map<std::string, CardData*>* cardListByName;
	std::vector<CardData*>* sortedCardList;
	
protected:
	CardList();
	~CardList();

private:

	static CardList* instance;
};

