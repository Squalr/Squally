#pragma once

#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"

using namespace cocos2d;

class CardShiftLeft : public CardData
{
public:
	CardShiftLeft();
	~CardShiftLeft();

private:
	static const std::string StringKeyCardName;
};
