#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal8 : public CardData
{
public:
	Decimal8();
	~Decimal8();

private:
	static const std::string StringKeyCardName;
};
