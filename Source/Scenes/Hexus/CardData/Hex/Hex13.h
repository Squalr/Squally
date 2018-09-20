#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex13 : public CardData
{
public:
	Hex13();
	~Hex13();

private:
	static const std::string StringKeyCardName;
};
