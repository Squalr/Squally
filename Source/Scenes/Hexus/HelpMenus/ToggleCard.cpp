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
	this->upToggleBin = ClickableNode::create(UIResources::Menus_Buttons_ArrowUpBlue, UIResources::Menus_Buttons_ArrowUpBlueSelected);
	this->downToggleBin = ClickableNode::create(UIResources::Menus_Buttons_ArrowDownBlue, UIResources::Menus_Buttons_ArrowDownBlueSelected);
	this->upToggleDec = ClickableNode::create(UIResources::Menus_Buttons_ArrowUpWhite, UIResources::Menus_Buttons_ArrowUpWhiteSelected);
	this->downToggleDec = ClickableNode::create(UIResources::Menus_Buttons_ArrowDownWhite, UIResources::Menus_Buttons_ArrowDownWhiteSelected);
	this->upToggleHex = ClickableNode::create(UIResources::Menus_Buttons_ArrowUpGreen, UIResources::Menus_Buttons_ArrowUpGreenSelected);
	this->downToggleHex = ClickableNode::create(UIResources::Menus_Buttons_ArrowDownGreen, UIResources::Menus_Buttons_ArrowDownGreenSelected);
	this->leftToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowLeft, UIResources::Menus_Buttons_ArrowLeftSelected);
	this->rightToggle = ClickableNode::create(UIResources::Menus_Buttons_ArrowRight, UIResources::Menus_Buttons_ArrowRightSelected);
    this->toggleModeLeftRight = toggleModeLeftRight;
    this->toggleModeUpDown = toggleModeUpDown;
    this->onToggleChange = nullptr;

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

    this->updateUpDownDisplays();

    this->addChild(this->upToggleBin);
    this->addChild(this->upToggleDec);
    this->addChild(this->upToggleHex);
    this->addChild(this->downToggleBin);
    this->addChild(this->downToggleDec);
    this->addChild(this->downToggleHex);
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

    this->upToggleBin->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNextDisplayType();
    });

    this->upToggleDec->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNextDisplayType();
    });

    this->upToggleHex->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->toggleNextDisplayType();
    });

    this->downToggleBin->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePreviousDisplayType();
    });

    this->downToggleDec->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePreviousDisplayType();
    });

    this->downToggleHex->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        this->togglePreviousDisplayType();
    });
}

void ToggleCard::initializePositions()
{
    super::initializePositions();

    this->upToggleBin->setPosition(Vec2(0.0f, 144.0f));
    this->downToggleBin->setPosition(Vec2(0.0f, -144.0f));
    this->upToggleDec->setPosition(Vec2(0.0f, 144.0f));
    this->downToggleDec->setPosition(Vec2(0.0f, -144.0f));
    this->upToggleHex->setPosition(Vec2(0.0f, 144.0f));
    this->downToggleHex->setPosition(Vec2(0.0f, -144.0f));
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

    this->updateUpDownDisplays();
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

    this->updateUpDownDisplays();
}

void ToggleCard::updateUpDownDisplays()
{
    this->upToggleBin->setVisible(false);
    this->upToggleDec->setVisible(false);
    this->upToggleHex->setVisible(false);
    this->downToggleBin->setVisible(false);
    this->downToggleDec->setVisible(false);
    this->downToggleHex->setVisible(false);
    
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
                    this->upToggleHex->setVisible(true);
                    this->downToggleDec->setVisible(true);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->upToggleBin->setVisible(true);
                    this->downToggleHex->setVisible(true);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->upToggleDec->setVisible(true);
                    this->downToggleBin->setVisible(true);
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
                    this->upToggleDec->setVisible(true);
                    this->downToggleDec->setVisible(true);
                    break;
                }
                case AutoCard::DisplayType::Decimal:
                {
                    this->upToggleBin->setVisible(true);
                    this->downToggleBin->setVisible(true);
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
                    this->upToggleHex->setVisible(true);
                    this->downToggleHex->setVisible(true);
                    break;
                }
                case AutoCard::DisplayType::Hex:
                {
                    this->upToggleDec->setVisible(true);
                    this->downToggleDec->setVisible(true);
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
                    this->upToggleBin->setVisible(true);
                    this->downToggleBin->setVisible(true);
                    break;
                }
                case AutoCard::DisplayType::Binary:
                {
                    this->upToggleHex->setVisible(true);
                    this->downToggleHex->setVisible(true);
                    break;
                }
            }

            break;
        }
    }
}
