#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary13 : public CardData
{
public:
	CardBinary13();
	~CardBinary13();

private:
	static const std::string StringKeyCardName;
};
