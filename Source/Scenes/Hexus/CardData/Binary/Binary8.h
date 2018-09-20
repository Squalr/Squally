#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary8 : public CardData
{
public:
	Binary8();
	~Binary8();

private:
	static const std::string StringKeyCardName;
};
