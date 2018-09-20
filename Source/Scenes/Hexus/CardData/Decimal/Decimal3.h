#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal3 : public CardData
{
public:
	Decimal3();
	~Decimal3();

private:
	static const std::string StringKeyCardName;
};
