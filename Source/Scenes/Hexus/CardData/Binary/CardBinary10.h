#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary10 : public CardData
{
public:
	CardBinary10();
	~CardBinary10();

private:
	static const std::string StringKeyCardName;
};
