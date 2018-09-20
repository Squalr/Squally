#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex8 : public CardData
{
public:
	CardHex8();
	~CardHex8();

private:
	static const std::string StringKeyCardName;
};
