#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex9 : public CardData
{
public:
	CardHex9();
	~CardHex9();

private:
	static const std::string StringKeyCardName;
};
