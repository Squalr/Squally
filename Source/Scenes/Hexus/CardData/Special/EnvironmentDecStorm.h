#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class EnvironmentDecStorm : public CardData
{
public:
	EnvironmentDecStorm();
	~EnvironmentDecStorm();

private:
	static const std::string StringKeyCardName;
};
