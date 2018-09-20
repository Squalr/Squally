#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardHex15 : public CardData
{
public:
	CardHex15();
	~CardHex15();

private:
	static const std::string StringKeyCardName;
};
