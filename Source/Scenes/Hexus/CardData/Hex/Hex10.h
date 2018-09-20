#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex10 : public CardData
{
public:
	Hex10();
	~Hex10();

private:
	static const std::string StringKeyCardName;
};
