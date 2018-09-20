#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex4 : public CardData
{
public:
	Hex4();
	~Hex4();

private:
	static const std::string StringKeyCardName;
};
