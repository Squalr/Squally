#include "HelpMenuComponent.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/HelpMenus/BinDecHexHelpMenu.h"
#include "Scenes/Hexus/HelpMenus/Flip1HelpMenu.h"
#include "Scenes/Hexus/HelpMenus/Flip2HelpMenu.h"
#include "Scenes/Hexus/HelpMenus/Flip3HelpMenu.h"
#include "Scenes/Hexus/HelpMenus/Flip4HelpMenu.h"
#include "Scenes/Hexus/HelpMenus/RolHelpMenu.h"
#include "Scenes/Hexus/HelpMenus/RorHelpMenu.h"
#include "Scenes/Hexus/HelpMenus/ShlHelpMenu.h"
#include "Scenes/Hexus/HelpMenus/ShrHelpMenu.h"

#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Exit.h"

using namespace cocos2d;

HelpMenuComponent* HelpMenuComponent::create()
{
    HelpMenuComponent* instance = new HelpMenuComponent();

    instance->autorelease();

    return instance;
}

HelpMenuComponent::HelpMenuComponent()
{
    LocalizedLabel* exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Exit::create());
    LocalizedLabel* exitLabelSelect = exitLabel->clone();

    exitLabel->enableOutline(Color4B::BLACK, 2);
    exitLabelSelect->enableOutline(Color4B::BLACK, 2);
    
    this->background = Sprite::create(HexusResources::StoreMenu_StoreBoard);
    this->textPanel = LayerColor::create(Color4B(0, 0, 0, 196), 1234, 196);
    this->binDecHexHelpMenu = BinDecHexHelpMenu::create();
    this->flip1HelpMenu = Flip1HelpMenu::create();
    this->flip2HelpMenu = Flip2HelpMenu::create();
    this->flip3HelpMenu = Flip3HelpMenu::create();
    this->flip4HelpMenu = Flip4HelpMenu::create();
    this->rolHelpMenu = RolHelpMenu::create();
    this->rorHelpMenu = RorHelpMenu::create();
    this->shlHelpMenu = ShlHelpMenu::create();
    this->shrHelpMenu = ShrHelpMenu::create();
    this->exitButton = ClickableTextNode::create(exitLabel, exitLabelSelect, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);
    this->onExit = nullptr;

    this->addChild(this->background);
    this->addChild(this->textPanel);
    this->addChild(this->binDecHexHelpMenu);
    this->addChild(this->flip1HelpMenu);
    this->addChild(this->flip2HelpMenu);
    this->addChild(this->flip3HelpMenu);
    this->addChild(this->flip4HelpMenu);
    this->addChild(this->rolHelpMenu);
    this->addChild(this->rorHelpMenu);
    this->addChild(this->shlHelpMenu);
    this->addChild(this->shrHelpMenu);
    this->addChild(this->exitButton);
}

HelpMenuComponent::~HelpMenuComponent()
{
}

void HelpMenuComponent::onEnter()
{
    super::onEnter();

    this->openMenu(nullptr);
    this->setVisible(false);
}

void HelpMenuComponent::initializePositions()
{
    super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

    this->textPanel->setPosition(Vec2(-1234.0f / 2.0f, 236.0f));
    this->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    this->exitButton->setPosition(Vec2(0.0f, -356.0f));
}

void HelpMenuComponent::setExitCallback(std::function<void()> onExit)
{
    this->onExit = onExit;

    this->exitButton->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
    {
        if (this->onExit != nullptr)
        {
            this->onExit();
        }
    });
}

void HelpMenuComponent::openMenu(Card* card)
{
    this->setVisible(true);
    this->binDecHexHelpMenu->setVisible(false);
    this->flip1HelpMenu->setVisible(false);
    this->flip2HelpMenu->setVisible(false);
    this->flip3HelpMenu->setVisible(false);
    this->flip4HelpMenu->setVisible(false);
    this->rolHelpMenu->setVisible(false);
    this->rorHelpMenu->setVisible(false);
    this->shlHelpMenu->setVisible(false);
    this->shrHelpMenu->setVisible(false);

    if (card == nullptr)
    {
        return;
    }

    switch (card->cardData->cardType)
    {
        case CardData::CardType::Binary:
        case CardData::CardType::Decimal:
        case CardData::CardType::Hexidecimal:
        {
            this->binDecHexHelpMenu->open(card);
            break;
        }
        case CardData::CardType::Special_FLIP1:
        {
            this->flip1HelpMenu->open();
            break;
        }
        case CardData::CardType::Special_FLIP2:
        {
            this->flip2HelpMenu->open();
            break;
        }
        case CardData::CardType::Special_FLIP3:
        {
            this->flip3HelpMenu->open();
            break;
        }
        case CardData::CardType::Special_FLIP4:
        {
            this->flip4HelpMenu->open();
            break;
        }
        case CardData::CardType::Special_ROL:
        {
            this->rolHelpMenu->open();
            break;
        }
        case CardData::CardType::Special_ROR:
        {
            this->rorHelpMenu->open();
            break;
        }
        case CardData::CardType::Special_SHL:
        {
            this->shlHelpMenu->open();
            break;
        }
        case CardData::CardType::Special_SHR:
        {
            this->shrHelpMenu->open();
            break;
        }
        default:
        {
            break;
        }
    }
}
