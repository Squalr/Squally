#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex12 : public CardData
{
public:
	Hex12();
	~Hex12();

private:
	static const std::string StringKeyCardName;
};
