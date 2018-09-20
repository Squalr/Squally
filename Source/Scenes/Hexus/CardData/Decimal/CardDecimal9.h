#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardDecimal9 : public CardData
{
public:
	CardDecimal9();
	~CardDecimal9();

private:
	static const std::string StringKeyCardName;
};
