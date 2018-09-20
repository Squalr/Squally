#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal10 : public CardData
{
public:
	Decimal10();
	~Decimal10();

private:
	static const std::string StringKeyCardName;
};
