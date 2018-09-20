#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary1 : public CardData
{
public:
	Binary1();
	~Binary1();

private:
	static const std::string StringKeyCardName;
};
