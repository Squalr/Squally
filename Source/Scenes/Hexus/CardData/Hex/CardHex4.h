#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex4 : public CardData
{
public:
	CardHex4();
	~CardHex4();

private:
	static const std::string StringKeyCardName;
};
