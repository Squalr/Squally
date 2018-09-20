#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary2 : public CardData
{
public:
	Binary2();
	~Binary2();

private:
	static const std::string StringKeyCardName;
};
