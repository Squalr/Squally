#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary3 : public CardData
{
public:
	Binary3();
	~Binary3();

private:
	static const std::string StringKeyCardName;
};
