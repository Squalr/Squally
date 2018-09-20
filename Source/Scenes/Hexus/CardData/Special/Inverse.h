#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Inverse : public CardData
{
public:
	Inverse();
	~Inverse();

private:
	static const std::string StringKeyCardName;
};
