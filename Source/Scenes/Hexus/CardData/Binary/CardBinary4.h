#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardBinary4 : public CardData
{
public:
	CardBinary4();
	~CardBinary4();

private:
	static const std::string StringKeyCardName;
};
