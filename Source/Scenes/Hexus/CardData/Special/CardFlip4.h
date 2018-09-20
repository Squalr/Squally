#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardFlip4 : public CardData
{
public:
	CardFlip4();
	~CardFlip4();

private:
	static const std::string StringKeyCardName;
};
