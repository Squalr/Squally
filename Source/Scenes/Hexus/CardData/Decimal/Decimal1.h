#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal1 : public CardData
{
public:
	Decimal1();
	~Decimal1();

private:
	static const std::string StringKeyCardName;
};
