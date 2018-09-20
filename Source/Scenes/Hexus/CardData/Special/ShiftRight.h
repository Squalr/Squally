#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class ShiftRight : public CardData
{
public:
	ShiftRight();
	~ShiftRight();

private:
	static const std::string StringKeyCardName;
};
