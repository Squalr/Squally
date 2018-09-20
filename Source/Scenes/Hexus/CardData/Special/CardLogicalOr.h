#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardLogicalOr : public CardData
{
public:
	CardLogicalOr();
	~CardLogicalOr();

private:
	static const std::string StringKeyCardName;
};
