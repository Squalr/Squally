#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex11 : public CardData
{
public:
	CardHex11();
	~CardHex11();

private:
	static const std::string StringKeyCardName;
};
