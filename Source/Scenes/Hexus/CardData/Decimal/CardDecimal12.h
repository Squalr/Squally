#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal12 : public CardData
{
public:
	CardDecimal12();
	~CardDecimal12();

private:
	static const std::string StringKeyCardName;
};
