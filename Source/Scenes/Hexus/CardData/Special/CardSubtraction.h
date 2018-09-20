#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardSubtraction : public CardData
{
public:
	CardSubtraction();
	~CardSubtraction();

private:
	static const std::string StringKeyCardName;
};
