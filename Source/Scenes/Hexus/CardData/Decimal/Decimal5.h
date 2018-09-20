#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal5 : public CardData
{
public:
	Decimal5();
	~Decimal5();

private:
	static const std::string StringKeyCardName;
};
