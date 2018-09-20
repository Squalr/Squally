#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Flip2 : public CardData
{
public:
	Flip2();
	~Flip2();

private:
	static const std::string StringKeyCardName;
};
