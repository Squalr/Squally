#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Flip1 : public CardData
{
public:
	Flip1();
	~Flip1();

private:
	static const std::string StringKeyCardName;
};
