#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex2 : public CardData
{
public:
	Hex2();
	~Hex2();

private:
	static const std::string StringKeyCardName;
};
