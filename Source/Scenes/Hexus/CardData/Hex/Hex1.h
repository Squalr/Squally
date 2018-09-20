#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex1 : public CardData
{
public:
	Hex1();
	~Hex1();

private:
	static const std::string StringKeyCardName;
};
