#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary4 : public CardData
{
public:
	Binary4();
	~Binary4();

private:
	static const std::string StringKeyCardName;
};
