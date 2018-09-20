#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal4 : public CardData
{
public:
	Decimal4();
	~Decimal4();

private:
	static const std::string StringKeyCardName;
};
