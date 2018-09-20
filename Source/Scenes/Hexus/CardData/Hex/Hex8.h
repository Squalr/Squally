#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex8 : public CardData
{
public:
	Hex8();
	~Hex8();

private:
	static const std::string StringKeyCardName;
};
