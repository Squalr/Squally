#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex3 : public CardData
{
public:
	Hex3();
	~Hex3();

private:
	static const std::string StringKeyCardName;
};
