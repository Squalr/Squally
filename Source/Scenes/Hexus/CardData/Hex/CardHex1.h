#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex1 : public CardData
{
public:
	CardHex1();
	~CardHex1();

private:
	static const std::string StringKeyCardName;
};
