#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex5 : public CardData
{
public:
	Hex5();
	~Hex5();

private:
	static const std::string StringKeyCardName;
};
