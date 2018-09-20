#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex6 : public CardData
{
public:
	Hex6();
	~Hex6();

private:
	static const std::string StringKeyCardName;
};
