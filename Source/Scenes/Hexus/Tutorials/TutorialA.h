#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/StateOverride.h"

using namespace cocos2d;

class TutorialA : public StateOverride
{
public:
	static TutorialA* create();

private:
	TutorialA();
	~TutorialA();
};
