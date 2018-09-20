#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class EnvironmentBinStorm : public CardData
{
public:
	EnvironmentBinStorm();
	~EnvironmentBinStorm();

private:
	static const std::string StringKeyCardName;
};
