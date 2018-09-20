#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal5 : public CardData
{
public:
	CardDecimal5();
	~CardDecimal5();

private:
	static const std::string StringKeyCardName;
};
