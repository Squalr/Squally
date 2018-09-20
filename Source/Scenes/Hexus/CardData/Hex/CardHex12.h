#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex12 : public CardData
{
public:
	CardHex12();
	~CardHex12();

private:
	static const std::string StringKeyCardName;
};
