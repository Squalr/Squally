#include "HelpMenuComponent.h"

#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/HelpMenus/BinDecHexHelpMenu.h"

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
    this->binDecHexHelpMenu = BinDecHexHelpMenu::create();
    this->exitButton = ClickableTextNode::create(exitLabel, exitLabelSelect, UIResources::Menus_Buttons_GenericButton, UIResources::Menus_Buttons_GenericButtonHover);
    this->onExit = nullptr;

    this->addChild(this->background);
    this->addChild(this->binDecHexHelpMenu);
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
            this->binDecHexHelpMenu->setVisible(true);
            break;
        }
        default:
        {
            break;
        }
    }
}
