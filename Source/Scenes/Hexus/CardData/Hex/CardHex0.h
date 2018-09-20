#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex0 : public CardData
{
public:
	CardHex0();
	~CardHex0();

private:
	static const std::string StringKeyCardName;
};
