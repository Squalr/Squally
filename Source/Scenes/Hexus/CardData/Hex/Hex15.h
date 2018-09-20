#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex15 : public CardData
{
public:
	Hex15();
	~Hex15();

private:
	static const std::string StringKeyCardName;
};
