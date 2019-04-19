#include "ToggleCard.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ToggleCard* ToggleCard::create(ToggleModeLeftRight toggleModeLeftRight,  ToggleModeUpDown toggleModeUpDown)
{
    ToggleCard* instance = new ToggleCard(toggleModeLeftRight, toggleModeUpDown);

    instance->autorelease();

    return instance;
}

ToggleCard::ToggleCard(ToggleModeLeftRight toggleModeLeftRight,  ToggleModeUpDown toggleModeUpDown)
{
    this->autoCard = AutoCard::create();
	this->upToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowUp, UIResources::Menus_Buttons_ArrowUpSelected);
	this->downToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowDown, UIResources::Menus_Buttons_ArrowDownSelected);
    this->toggleModeLeftRight = toggleModeLeftRight;
    this->toggleModeUpDown = toggleModeUpDown;
    this->onToggleChange = nullptr;

    this->addChild(this->upToggle);
    this->addChild(this->downToggle);
    this->addChild(this->leftToggle);
    this->addChild(this->rightToggle);
    this->addChild(this->autoCard);
}

ToggleCard::~ToggleCard()
{
}

void ToggleCard::onEnter()
{
    super::onEnter();

    switch(this->toggleModeLeftRight)
    {
        case ToggleModeLeftRight::Hidden:
        {
            this->leftToggle->setVisible(false);
            this->rightToggle->setVisible(false);
            break;
        }
        default:
        case ToggleModeLeftRight::LeftRight:
        {
            break;
        }
    }
    
    switch(this->toggleModeUpDown)
    {
        case ToggleModeUpDown::Hidden:
        {
            this->upToggle->setVisible(false);
            this->downToggle->setVisible(false);
            return;
        }
        default:
        case ToggleModeUpDown::BinDecHex:
        case ToggleModeUpDown::BinDec:
        case ToggleModeUpDown::DecHex:
        case ToggleModeUpDown::HexBin:
        {
            this->upToggle->setVisible(true);
            this->downToggle->setVisible(true);

            break;
        }
    }
}

void ToggleCard::initializeListeners()
{
    super::initializeListeners();

    this->rightToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNextValue();
    });

    this->leftToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePreviousValue();
    });

    this->upToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNextDisplayType();
    });

    this->downToggle->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePreviousDisplayType();
    });
}

void ToggleCard::initializePositions()
{
    super::initializePositions();

    this->upToggle->setPosition(Vec2(0.0f, 144.0f));
    this->downToggle->setPosition(Vec2(0.0f, -144.0f));
    this->leftToggle->setPosition(Vec2(-112.0f, 0.0f));
    this->rightToggle->setPosition(Vec2(112.0f, 0.0f));
}

void ToggleCard::setToggleCallback(std::function<void()> onToggleChange)
{
    this->onToggleChange = onToggleChange;
}

void ToggleCard::toggleNextValue()
{
    this->autoCard->incrementAttack();

    if (this->onToggleChange != nullptr)
    {
        this->onToggleChange();
    }
}

void ToggleCard::togglePreviousValue()
{
    this->autoCard->decrementAttack();

    if (this->onToggleChange != nullptr)
    {
        this->onToggleChange();
    }
}

void ToggleCard::toggleNextDisplayType()
{
    switch(this->toggleModeUpDown)
    {
        default:
        case ToggleModeUpDown::Hidden:
        {
            return;
        }
        case ToggleModeUpDown::BinDecHex:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::BinDec:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::DecHex:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::HexBin:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
            }

            break;
        }
    }
}

void ToggleCard::togglePreviousDisplayType()
{
    switch(this->toggleModeUpDown)
    {
        default:
        case ToggleModeUpDown::Hidden:
        {
            return;
        }
        case ToggleModeUpDown::BinDecHex:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::BinDec:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::DecHex:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Decimal:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Decimal);
                    break;
                }
            }

            break;
        }
        case ToggleModeUpDown::HexBin:
        {
            switch(this->autoCard->getDisplayType())
            {
                default:
                case AutoCard::DisplayType::Hex:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Binary);
                    break;
                }
                case AutoCard::DisplayType::Binary:
                {
                    this->autoCard->setDisplayType(AutoCard::DisplayType::Hex);
                    break;
                }
            }

            break;
        }
    }
}
