#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class ShiftLeft : public CardData
{
public:
	ShiftLeft();
	~ShiftLeft();

private:
	static const std::string StringKeyCardName;
};
