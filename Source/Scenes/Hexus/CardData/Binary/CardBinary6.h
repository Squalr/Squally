#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary6 : public CardData
{
public:
	CardBinary6();
	~CardBinary6();

private:
	static const std::string StringKeyCardName;
};
