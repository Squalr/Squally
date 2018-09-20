#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary9 : public CardData
{
public:
	Binary9();
	~Binary9();

private:
	static const std::string StringKeyCardName;
};
