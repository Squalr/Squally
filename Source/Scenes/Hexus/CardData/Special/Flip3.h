#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Flip3 : public CardData
{
public:
	Flip3();
	~Flip3();

private:
	static const std::string StringKeyCardName;
};
