#include "MinigamesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Menus/MenuBackground.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Back.h"
#include "Strings/Menus/ComingSoon.h"
#include "Strings/Hexus/Hexus.h"
#include "Strings/Hexus/HexusPuzzles.h"

using namespace cocos2d;

MinigamesMenu* MinigamesMenu::instance;

void MinigamesMenu::registerGlobalScene()
{
	if (MinigamesMenu::instance == nullptr)
	{
		MinigamesMenu::instance = new MinigamesMenu();

		MinigamesMenu::instance->autorelease();
		MinigamesMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(MinigamesMenu::instance);
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
	this->scrollPane = ScrollPane::create(Size(1152.0f, 768.0f), Color4B(0, 0, 0, 127));

	LocalizedLabel*	backButtonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());
	LocalizedLabel*	backButtonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Back::create());

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	LocalizedLabel*	hexusLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Hexus::create());
	LocalizedLabel*	hexusLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Hexus::create());

	hexusLabel->setColor(textColor);
	hexusLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabel->enableGlow(shadowColor);

	hexusLabelHover->setColor(highlightColor);
	hexusLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusLabelHover->enableGlow(glowColor);

	this->hexusButton = TextMenuSprite::create(
		hexusLabel,
		hexusLabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	this->hexusButton->setTextOffset(labelOffset);

	Sprite* hexusIcon = Sprite::create(UIResources::Menus_Icons_Banner);

	hexusIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	hexusIcon->setPosition(Vec2(-this->hexusButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->hexusButton->addChild(hexusIcon);
	this->hexusButton->setClickSound(SoundResources::Menus_Simple_Button);

	LocalizedLabel*	hexusPuzzlesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_HexusPuzzles::create());
	LocalizedLabel*	hexusPuzzlesLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_HexusPuzzles::create());

	hexusPuzzlesLabel->setColor(textColor);
	hexusPuzzlesLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusPuzzlesLabel->enableGlow(shadowColor);

	hexusPuzzlesLabelHover->setColor(highlightColor);
	hexusPuzzlesLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	hexusPuzzlesLabelHover->enableGlow(glowColor);

	this->hexusPuzzlesButton = TextMenuSprite::create(
		hexusPuzzlesLabel,
		hexusPuzzlesLabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	this->hexusPuzzlesButton->setTextOffset(labelOffset);

	// TODO: Temp for demo
	this->hexusPuzzlesButton->disableInteraction(128);

	Sprite* hexusPuzzlesIcon = Sprite::create(UIResources::Menus_Icons_Gauntlet);

	hexusPuzzlesIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	hexusPuzzlesIcon->setPosition(Vec2(-this->hexusPuzzlesButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	this->hexusPuzzlesButton->addChild(hexusPuzzlesIcon);

	this->comingSoonButton1 = this->createComingSoonButton();
	this->comingSoonButton2 = this->createComingSoonButton();
	this->comingSoonButton3 = this->createComingSoonButton();
	this->comingSoonButton4 = this->createComingSoonButton();
	this->comingSoonButton5 = this->createComingSoonButton();
	this->comingSoonButton6 = this->createComingSoonButton();

	this->addChild(this->backgroundNode);
	this->scrollPane->addChild(this->hexusButton);
	this->scrollPane->addChild(this->hexusPuzzlesButton);
	this->scrollPane->addChild(this->comingSoonButton1);
	this->scrollPane->addChild(this->comingSoonButton2);
	this->scrollPane->addChild(this->comingSoonButton3);
	this->scrollPane->addChild(this->comingSoonButton4);
	this->scrollPane->addChild(this->comingSoonButton5);
	this->scrollPane->addChild(this->comingSoonButton6);
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

void MinigamesMenu::initializeListeners()
{
	super::initializeListeners();

	MinigamesMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateMinigames, [](EventCustom* args)
	{
		GlobalDirector::loadScene(MinigamesMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(MinigamesMenu::onKeyPressed, this);
	this->hexusButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusClick, this));
	this->hexusPuzzlesButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onHexusPuzzlesClick, this));
	this->backButton->setClickCallback(CC_CALLBACK_1(MinigamesMenu::onBackClick, this));

	this->addEventListener(keyboardListener);
}

void MinigamesMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size paneSize = this->scrollPane->getPaneSize();

	this->scrollPane->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	this->hexusButton->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 7 + 128.0f));
	this->hexusPuzzlesButton->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 6 + 128.0f));
	this->comingSoonButton1->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 5 + 128.0f));
	this->comingSoonButton2->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 4 + 128.0f));
	this->comingSoonButton3->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 3 + 128.0f));
	this->comingSoonButton4->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 2 + 128.0f));
	this->comingSoonButton5->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 1 + 128.0f));
	this->comingSoonButton6->setPosition(Vec2(paneSize.width / 2.0f, 192.0f * 0 + 128.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->scrollPane->fitSizeToContent();
}

void MinigamesMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void MinigamesMenu::onBackClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void MinigamesMenu::onHexusClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateHexusChapterSelect();
}

void MinigamesMenu::onHexusPuzzlesClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateHexusPuzzles();
}

TextMenuSprite* MinigamesMenu::createComingSoonButton()
{
	const Size shadowSize = Size(-2.0f, -2.0f);
	const int shadowBlur = 2;
	const int hoverOutlineSize = 2;
	const Color3B textColor = Color3B::WHITE;
	const Color4B shadowColor = Color4B::BLACK;
	const Color3B highlightColor = Color3B::YELLOW;
	const Color4B glowColor = Color4B::ORANGE;
	const Vec2 labelOffset = Vec2(48.0f, 0.0f);

	LocalizedLabel*	comingSoonLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_ComingSoon::create());
	LocalizedLabel*	comingSoonLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_ComingSoon::create());

	comingSoonLabel->setColor(textColor);
	comingSoonLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	comingSoonLabel->enableGlow(shadowColor);

	comingSoonLabelHover->setColor(highlightColor);
	comingSoonLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	comingSoonLabelHover->enableGlow(glowColor);

	TextMenuSprite* comingSoonButton = TextMenuSprite::create(
		comingSoonLabel,
		comingSoonLabelHover,
		UIResources::Menus_MinigamesMenu_Banner,
		UIResources::Menus_MinigamesMenu_BannerHover);

	comingSoonButton->setTextOffset(labelOffset);

	Sprite* lockIcon = Sprite::create(UIResources::Menus_Icons_Lock);

	comingSoonButton->addChild(lockIcon);
	comingSoonButton->disableInteraction(128);

	lockIcon->setAnchorPoint(Vec2(0.0f, 0.5f));
	lockIcon->setPosition(Vec2(-comingSoonButton->getContentSize().width / 2.0f + 78.0f, 0.0f));

	return comingSoonButton;
}