#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardInverse : public CardData
{
public:
	CardInverse();
	~CardInverse();

private:
	static const std::string StringKeyCardName;
};
