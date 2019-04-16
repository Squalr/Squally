#include "ToggleCard.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"

using namespace cocos2d;

ToggleCard* ToggleCard::create()
{
    ToggleCard* instance = new ToggleCard();

    instance->autorelease();

    return instance;
}

ToggleCard::ToggleCard()
{
    this->autoCard = AutoCard::create();

    this->addChild(this->autoCard);
}

ToggleCard::~ToggleCard()
{
}

void ToggleCard::onEnter()
{
    super::onEnter();
}
