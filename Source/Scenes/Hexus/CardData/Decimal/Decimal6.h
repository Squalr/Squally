#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal6 : public CardData
{
public:
	Decimal6();
	~Decimal6();

private:
	static const std::string StringKeyCardName;
};
