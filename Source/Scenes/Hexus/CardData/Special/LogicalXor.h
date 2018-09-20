#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class LocialXor : public CardData
{
public:
	LocialXor();
	~LocialXor();

private:
	static const std::string StringKeyCardName;
};
