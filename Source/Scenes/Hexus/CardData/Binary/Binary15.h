#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class Binary15 : public CardData
{
public:
	Binary15();
	~Binary15();

private:
	static const std::string StringKeyCardName;
};
