#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardLogicalXor : public CardData
{
public:
	CardLogicalXor();
	~CardLogicalXor();

private:
	static const std::string StringKeyCardName;
};
