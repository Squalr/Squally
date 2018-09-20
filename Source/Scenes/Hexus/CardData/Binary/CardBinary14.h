#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary14 : public CardData
{
public:
	CardBinary14();
	~CardBinary14();

private:
	static const std::string StringKeyCardName;
};
