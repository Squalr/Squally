#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex0 : public CardData
{
public:
	Hex0();
	~Hex0();

private:
	static const std::string StringKeyCardName;
};
