#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary1 : public CardData
{
public:
	CardBinary1();
	~CardBinary1();

private:
	static const std::string StringKeyCardName;
};
