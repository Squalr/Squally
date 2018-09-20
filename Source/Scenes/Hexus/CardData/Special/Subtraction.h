#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Subtraction : public CardData
{
public:
	Subtraction();
	~Subtraction();

private:
	static const std::string StringKeyCardName;
};
