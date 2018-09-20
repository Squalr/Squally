#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class EnvironmentClear : public CardData
{
public:
	EnvironmentClear();
	~EnvironmentClear();

private:
	static const std::string StringKeyCardName;
};
