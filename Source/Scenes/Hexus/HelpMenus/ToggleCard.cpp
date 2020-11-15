#include "ToggleCard.h"

#include "Engine/Input/ClickableNode.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

ToggleCard* ToggleCard::create(ToggleModeLeftRight toggleModeLeftRight, ToggleModeUpDown toggleModeUpDown)
{
    ToggleCard* instance = new ToggleCard(toggleModeLeftRight, toggleModeUpDown);

    instance->autorelease();

    return instance;
}

ToggleCard::ToggleCard(ToggleModeLeftRight toggleModeLeftRight, ToggleModeUpDown toggleModeUpDown)
{
    this->autoCard = AutoCard::create();
	this->upToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowUp, UIResources::Menus_Buttons_ArrowUpSelected);
	this->downToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowDown, UIResources::Menus_Buttons_ArrowDownSelected);
	this->leftToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowLeft, UIResources::Menus_Buttons_ArrowLeftSelected);
	this->rightToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowRight, UIResources::Menus_Buttons_ArrowRightSelected);
    this->toggleModeLeftRight = toggleModeLeftRight;
    this->toggleModeUpDown = toggleModeUpDown;
    this->onToggleAttackChange = nullptr;

    this->upToggle->setClickSound(SoundResources::Menus_ButtonClick4);
    this->downToggle->setClickSound(SoundResources::Menus_ButtonClick4);
    this->leftToggle->setClickSound(SoundResources::Menus_ButtonClick4);
    this->rightToggle->setClickSound(SoundResources::Menus_ButtonClick4);

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

    this->rightToggle->setMouseClickCallback([=](MouseEventArgs*)
    {
        this->toggleNextValue();
    });

    this->leftToggle->setMouseClickCallback([=](MouseEventArgs*)
    {
        this->togglePreviousValue();
    });

    this->upToggle->setMouseClickCallback([=](MouseEventArgs*)
    {
        this->toggleNextDisplayType();
    });

    this->downToggle->setMouseClickCallback([=](MouseEventArgs*)
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

void ToggleCard::setToggleAttackCallback(std::function<void()> onToggleAttackChange)
{
    this->onToggleAttackChange = onToggleAttackChange;
}

void ToggleCard::setToggleDisplayTypeCallback(std::function<void()> onToggleDisplayTypeChange)
{
    this->onToggleDisplayTypeChange = onToggleDisplayTypeChange;
}

void ToggleCard::setDisplayType(AutoCard::DisplayType displayType, bool triggerCallback)
{
    this->autoCard->setDisplayType(displayType);

    if (triggerCallback)
    {
        if (this->onToggleDisplayTypeChange != nullptr)
        {
            this->onToggleDisplayTypeChange();
        }
    }
}

void ToggleCard::toggleNextValue()
{
    this->autoCard->incrementAttack();

    if (this->onToggleAttackChange != nullptr)
    {
        this->onToggleAttackChange();
    }
}

void ToggleCard::togglePreviousValue()
{
    this->autoCard->decrementAttack();

    if (this->onToggleAttackChange != nullptr)
    {
        this->onToggleAttackChange();
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

    if (this->onToggleDisplayTypeChange != nullptr)
    {
        this->onToggleDisplayTypeChange();
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

    if (this->onToggleDisplayTypeChange != nullptr)
    {
        this->onToggleDisplayTypeChange();
    }
}

void ToggleCard::setAttack(int attack)
{
    this->autoCard->setAttack(attack);
}

int ToggleCard::getAttack()
{
    return this->autoCard->getAttack();
}

void ToggleCard::setCardScale(float cardScale)
{
    this->autoCard->setCardScale(cardScale);
}
