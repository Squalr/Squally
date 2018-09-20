#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Hex9 : public CardData
{
public:
	Hex9();
	~Hex9();

private:
	static const std::string StringKeyCardName;
};
