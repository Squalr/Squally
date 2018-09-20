#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary10 : public CardData
{
public:
	Binary10();
	~Binary10();

private:
	static const std::string StringKeyCardName;
};
