#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardEnvironmentClear : public CardData
{
public:
	CardEnvironmentClear();
	~CardEnvironmentClear();

private:
	static const std::string StringKeyCardName;
};
