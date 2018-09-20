#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal7 : public CardData
{
public:
	Decimal7();
	~Decimal7();

private:
	static const std::string StringKeyCardName;
};
