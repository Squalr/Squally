#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal2 : public CardData
{
public:
	CardDecimal2();
	~CardDecimal2();

private:
	static const std::string StringKeyCardName;
};
