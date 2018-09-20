#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal2 : public CardData
{
public:
	Decimal2();
	~Decimal2();

private:
	static const std::string StringKeyCardName;
};
