#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardLogicalAnd : public CardData
{
public:
	CardLogicalAnd();
	~CardLogicalAnd();

private:
	static const std::string StringKeyCardName;
};
