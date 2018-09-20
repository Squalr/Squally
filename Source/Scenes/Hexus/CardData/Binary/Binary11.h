#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary11 : public CardData
{
public:
	Binary11();
	~Binary11();

private:
	static const std::string StringKeyCardName;
};
