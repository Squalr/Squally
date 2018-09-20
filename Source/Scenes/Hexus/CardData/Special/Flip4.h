#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Flip4 : public CardData
{
public:
	Flip4();
	~Flip4();

private:
	static const std::string StringKeyCardName;
};
