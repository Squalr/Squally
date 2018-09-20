#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex7 : public CardData
{
public:
	Hex7();
	~Hex7();

private:
	static const std::string StringKeyCardName;
};
