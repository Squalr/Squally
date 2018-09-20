#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal4 : public CardData
{
public:
	CardDecimal4();
	~CardDecimal4();

private:
	static const std::string StringKeyCardName;
};
