#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal1 : public CardData
{
public:
	CardDecimal1();
	~CardDecimal1();

private:
	static const std::string StringKeyCardName;
};
