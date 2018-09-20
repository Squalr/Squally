#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Addition : public CardData
{
public:
	Addition();
	~Addition();

private:
	static const std::string StringKeyCardName;
};
