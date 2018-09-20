#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary5 : public CardData
{
public:
	Binary5();
	~Binary5();

private:
	static const std::string StringKeyCardName;
};
