#include "ToggleCard.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ToggleCard* ToggleCard::create(ToggleMode toggleMode)
{
    ToggleCard* instance = new ToggleCard(toggleMode);

    instance->autorelease();

    return instance;
}

ToggleCard::ToggleCard(ToggleMode toggleMode)
{
    this->autoCard = AutoCard::create();
	this->upToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowUp, UIResources::Menus_Buttons_ArrowUpSelected);
	this->downToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowDown, UIResources::Menus_Buttons_ArrowDownSelected);
	this->leftToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowLeft, UIResources::Menus_Buttons_ArrowLeftSelected);
	this->rightToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowRight, UIResources::Menus_Buttons_ArrowRightSelected);
    this->onToggleChange = nullptr;

    switch(toggleMode)
    {
        default:
        case ToggleMode::Hidden:
        {
            this->upToggle->setVisible(false);
            this->downToggle->setVisible(false);
            this->leftToggle->setVisible(false);
            this->rightToggle->setVisible(false);
            break;
        }
        case ToggleMode::LeftRight:
        {
            this->upToggle->setVisible(false);
            this->downToggle->setVisible(false);
            break;
        }
        case ToggleMode::UpDown:
        {
            this->leftToggle->setVisible(false);
            this->rightToggle->setVisible(false);
            break;
        }
    }

    this->addChild(this->autoCard);
    this->addChild(this->upToggle);
    this->addChild(this->downToggle);
    this->addChild(this->leftToggle);
    this->addChild(this->rightToggle);
}

ToggleCard::~ToggleCard()
{
}

void ToggleCard::onEnter()
{
    super::onEnter();
}

void ToggleCard::initializeListeners()
{
    super::initializeListeners();

    this->upToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNext();
    });

    this->rightToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNext();
    });

    this->leftToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePrevious();
    });

    this->downToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePrevious();
    });
}

void ToggleCard::initializePositions()
{
    super::initializePositions();

    this->upToggle->setPosition(Vec2(0.0f, -160.0f));
    this->downToggle->setPosition(Vec2(0.0f, 160.0f));
    this->leftToggle->setPosition(Vec2(-112.0f, 0.0f));
    this->rightToggle->setPosition(Vec2(112.0f, 0.0f));
}

void ToggleCard::setToggleCallback(std::function<void()> onToggleChange)
{
    this->onToggleChange = onToggleChange;
}

void ToggleCard::toggleNext()
{
    this->autoCard->incrementAttack();

    if (this->onToggleChange != nullptr)
    {
        this->onToggleChange();
    }
}

void ToggleCard::togglePrevious()
{
    this->autoCard->decrementAttack();

    if (this->onToggleChange != nullptr)
    {
        this->onToggleChange();
    }
}
