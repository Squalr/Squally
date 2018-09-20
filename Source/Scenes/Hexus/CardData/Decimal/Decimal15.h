#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal15 : public CardData
{
public:
	Decimal15();
	~Decimal15();

private:
	static const std::string StringKeyCardName;
};
