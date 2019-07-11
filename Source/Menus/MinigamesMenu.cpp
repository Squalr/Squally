#include "MinigamesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/MenuBackground.h"
#include "Scenes/Cipher/CipherMenu/ChapterSelect/CipherChapterSelectMenu.h"
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterSelectMenu.h"
#include "Scenes/Hexus/Menus/ChapterSelect/HexusChapterSelectMenuPuzzles.h"
#include "Scenes/PointerTrace/Menus/LevelSelect/PointerTraceLevelSelect.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Cipher/Cipher.h"
#include "Strings/Hexus/Hexus.h"
#include "Strings/Hexus/HexusPuzzles.h"
#include "Strings/Menus/Back.h"
#include "Strings/Menus/ComingSoon.h"
#include "Strings/PointerTrace/PointerTrace.h"
#include "Strings/Stacks/Stacks.h"
#include "Strings/SpaceForce/SpaceForce.h"
#include "Strings/TowerDefense/TowerDefense.h"

using namespace cocos2d;

MinigamesMenu* MinigamesMenu::instance;

MinigamesMenu* MinigamesMenu::getInstance()
{
	if (MinigamesMenu::instance == nullptr)
	{
		MinigamesMenu::instance = new MinigamesMenu();

		MinigamesMenu::instance->autorelease();
		MinigamesMenu::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(MinigamesMenu::instance);
	}

	return MinigamesMenu::instance;
}

MinigamesMenu::MinigamesMenu()
{
	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	this->backgroundNode = Node::create();
	this->scrollPane = ScrollPane::create(Size(1152.0f, 768.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);

	LocalizedLabel*	backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel*	backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = ClickableTextNode::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->hexusButton = this->createButton(Strings::Hexus_Hexus::create(), UIResources::Menus_Icons_Banner);
	this->hexusPuzzlesButton = this->createButton(Strings::Hexus_HexusPuzzles::create(), UIResources::Menus_Icons_Gauntlet);
	this->pointerTraceButton = this->createButton(Strings::PointerTrace_PointerTrace::create(), UIResources::Menus_Icons_SpellCast);
	this->cipherButton = this->createButton(Strings::Cipher_Cipher::create(), UIResources::Menus_Icons_KeyGold);
	this->stacksButton = this->createButton(Strings::Stacks_Stacks::create(), UIResources::Menus_Icons_Scale);
	this->towerDefenseButton = this->createButton(Strings::TowerDefense_TowerDefense::create(), UIResources::Menus_Icons_Meteor);
	this->spaceForceButton = this->createButton(Strings::SpaceForce_SpaceForce::create(), UIResources::Menus_Icons_Stars);

	this->cipherButton->disableInteraction(128);
	this->stacksButton->disableInteraction(128);
	this->towerDefenseButton->disableInteraction(128);
	this->spaceForceButton->disableInteraction(128);

	this->addChild(this->backgroundNode);
	this->scrollPane->addChild(this->hexusButton);
	this->scrollPane->addChild(this->hexusPuzzlesButton);
	this->scrollPane->addChild(this->cipherButton);
	this->scrollPane->addChild(this->pointerTraceButton);
	this->scrollPane->addChild(this->stacksButton);
	this->scrollPane->addChild(this->towerDefenseButton);
	this->scrollPane->addChild(this->spaceForceButton);
	this->addChild(this->scrollPane);
	this->addChild(this->backButton);
}

MinigamesMenu::~MinigamesMenu()
{
}

void MinigamesMenu::onEnter()
{
	super::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);
	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->backgroundNode->addChild(MenuBackground::claimInstance());

	this->scheduleUpdate();
}

void MinigamesMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->hexusButton->setPosition(Vec2(0.0f, -192.0f * 0 - 128.0f));
	this->hexusPuzzlesButton->setPosition(Vec2(0.0f, -192.0f * 1 - 128.0f));
	this->pointerTraceButton->setPosition(Vec2(0.0f, -192.0f * 2 - 128.0f));
	this->cipherButton->setPosition(Vec2(0.0f, -192.0f * 3 - 128.0f));
	this->stacksButton->setPosition(Vec2(0.0f, -192.0f * 4 - 128.0f));
	this->towerDefenseButton->setPosition(Vec2(0.0f, -192.0f * 5 - 128.0f));
	this->spaceForceButton->setPosition(Vec2(0.0f, -192.0f * 6 - 128.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
}

void MinigamesMenu::initializeListeners()
{
	super::initializeListeners();

	this->hexusButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(HexusChapterSelectMenu::getInstance()); });
	this->hexusPuzzlesButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(HexusChapterSelectMenuPuzzles::getInstance()); });
	this->pointerTraceButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(PointerTraceLevelSelect::getInstance()); });
	this->cipherButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(CipherChapterSelectMenu::getInstance()); });
	this->stacksButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(CipherChapterSelectMenu::getInstance()); });
	this->towerDefenseButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(CipherChapterSelectMenu::getInstance()); });
	this->spaceForceButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(CipherChapterSelectMenu::getInstance()); });
	this->backButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*){ NavigationEvents::LoadScene(TitleScreen::getInstance()); });

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		NavigationEvents::LoadScene(TitleScreen::getInstance());
	});
}

ClickableTextNode* MinigamesMenu::createButton(LocalizedString* text, std::string iconResource)
{
	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	LocalizedLabel*	comingSoonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, text);
	LocalizedLabel*	comingSoonLabelHover = comingSoonLabel->clone();

	comingSoonLabel->setColor(textColor);
	comingSoonLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	comingSoonLabel->enableGlow(shadowColor);

	comingSoonLabelHover->setColor(highlightColor);
	comingSoonLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	comingSoonLabelHover->enableGlow(glowColor);

	ClickableTextNode* comingSoonButton = ClickableTextNode::create(
		comingSoonLabel,
		comingSoonLabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	comingSoonButton->setTextOffset(labelOffset);

	Sprite* icon = Sprite::create(iconResource);

	comingSoonButton->addChild(icon);

	icon->setAnchorPoint(Vec2(0.0f, 0.5f));
	icon->setPosition(Vec2(-comingSoonButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	return comingSoonButton;
}

ClickableTextNode* MinigamesMenu::createComingSoonButton()
{
	ClickableTextNode* comingSoonButton = this->createButton(Strings::Menus_ComingSoon::create(), UIResources::Menus_Icons_Lock);
	
	comingSoonButton->disableInteraction(128);

	return comingSoonButton;
}