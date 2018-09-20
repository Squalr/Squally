#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Decimal9 : public CardData
{
public:
	Decimal9();
	~Decimal9();

private:
	static const std::string StringKeyCardName;
};
