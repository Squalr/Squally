#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex11 : public CardData
{
public:
	Hex11();
	~Hex11();

private:
	static const std::string StringKeyCardName;
};
