#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/Binary/Binary0.h"
#include "Scenes/Hexus/CardData/Binary/Binary1.h"
#include "Scenes/Hexus/CardData/Binary/Binary2.h"
#include "Scenes/Hexus/CardData/Binary/Binary3.h"
#include "Scenes/Hexus/CardData/Binary/Binary4.h"
#include "Scenes/Hexus/CardData/Binary/Binary5.h"
#include "Scenes/Hexus/CardData/Binary/Binary6.h"
#include "Scenes/Hexus/CardData/Binary/Binary7.h"
#include "Scenes/Hexus/CardData/Binary/Binary8.h"
#include "Scenes/Hexus/CardData/Binary/Binary9.h"
#include "Scenes/Hexus/CardData/Binary/Binary10.h"
#include "Scenes/Hexus/CardData/Binary/Binary11.h"
#include "Scenes/Hexus/CardData/Binary/Binary12.h"
#include "Scenes/Hexus/CardData/Binary/Binary13.h"
#include "Scenes/Hexus/CardData/Binary/Binary14.h"
#include "Scenes/Hexus/CardData/Binary/Binary15.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal0.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal1.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal2.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal3.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal4.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal5.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal6.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal7.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal8.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal9.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal10.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal11.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal12.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal13.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal14.h"
#include "Scenes/Hexus/CardData/Decimal/Decimal15.h"
#include "Scenes/Hexus/CardData/Hex/Hex0.h"
#include "Scenes/Hexus/CardData/Hex/Hex1.h"
#include "Scenes/Hexus/CardData/Hex/Hex2.h"
#include "Scenes/Hexus/CardData/Hex/Hex3.h"
#include "Scenes/Hexus/CardData/Hex/Hex4.h"
#include "Scenes/Hexus/CardData/Hex/Hex5.h"
#include "Scenes/Hexus/CardData/Hex/Hex6.h"
#include "Scenes/Hexus/CardData/Hex/Hex7.h"
#include "Scenes/Hexus/CardData/Hex/Hex8.h"
#include "Scenes/Hexus/CardData/Hex/Hex9.h"
#include "Scenes/Hexus/CardData/Hex/Hex10.h"
#include "Scenes/Hexus/CardData/Hex/Hex11.h"
#include "Scenes/Hexus/CardData/Hex/Hex12.h"
#include "Scenes/Hexus/CardData/Hex/Hex13.h"
#include "Scenes/Hexus/CardData/Hex/Hex14.h"
#include "Scenes/Hexus/CardData/Hex/Hex15.h"
#include "Scenes/Hexus/CardData/Special/Addition.h"
#include "Scenes/Hexus/CardData/Special/EnvironmentBinStorm.h"
#include "Scenes/Hexus/CardData/Special/EnvironmentDecStorm.h"
#include "Scenes/Hexus/CardData/Special/EnvironmentHexStorm.h"
#include "Scenes/Hexus/CardData/Special/Flip1.h"
#include "Scenes/Hexus/CardData/Special/Flip2.h"
#include "Scenes/Hexus/CardData/Special/Flip3.h"
#include "Scenes/Hexus/CardData/Special/Flip4.h"
#include "Scenes/Hexus/CardData/Special/Inverse.h"
#include "Scenes/Hexus/CardData/Special/LogicalAnd.h"
#include "Scenes/Hexus/CardData/Special/LogicalOr.h"
#include "Scenes/Hexus/CardData/Special/LogicalXor.h"
#include "Scenes/Hexus/CardData/Special/ShiftLeft.h"
#include "Scenes/Hexus/CardData/Special/ShiftRight.h"
#include "Scenes/Hexus/CardData/Special/Subtraction.h"

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

