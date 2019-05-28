#include "TitleScreen.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCParticleExamples.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Music.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Title/TitleScreenBackground.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Exit.h"
#include "Strings/Menus/Minigames.h"
#include "Strings/Menus/Options/Options.h"
#include "Strings/Menus/StoryMode.h"

using namespace cocos2d;

TitleScreen* TitleScreen::instance = nullptr;

TitleScreen* TitleScreen::getInstance()
{
	if (TitleScreen::instance == nullptr)
	{
		TitleScreen::instance = new TitleScreen();

		TitleScreen::instance->autorelease();
		TitleScreen::instance->initializeListeners();
	}

	return TitleScreen::instance;
}

void TitleScreen::registerGlobalScene()
{
	GlobalDirector::registerGlobalScene(TitleScreen::getInstance());
}

TitleScreen::TitleScreen()
{
	this->titleBar = Sprite::create(UIResources::Menus_TitleScreen_TitleBar);
	this->title = Sprite::create(UIResources::Menus_TitleScreen_Title);
	this->background = TitleScreenBackground::create();
	this->music = Music::create(MusicResources::WeWillGetThereTogether);
	
	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	LocalizedLabel*	storyModeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_StoryMode::create());
	LocalizedLabel*	storyModeLabelHover = storyModeLabel->clone();

	LocalizedLabel*	minigamesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Minigames::create());
	LocalizedLabel*	minigamesLabelHover = minigamesLabel->clone();

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Options_Options::create());
	LocalizedLabel*	optionsLabelHover = optionsLabel->clone();

	LocalizedLabel*	exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Exit::create());
	LocalizedLabel*	exitLabelHover = exitLabel->clone();

	storyModeLabel->setColor(textColor);
	storyModeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabel->enableGlow(shadowColor);
	minigamesLabel->setColor(textColor);
	minigamesLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	minigamesLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);

	storyModeLabelHover->setColor(highlightColor);
	storyModeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabelHover->enableGlow(glowColor);
	minigamesLabelHover->setColor(highlightColor);
	minigamesLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	minigamesLabelHover->enableGlow(glowColor);
	optionsLabelHover->setColor(highlightColor);
	optionsLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelHover->enableGlow(glowColor);
	exitLabelHover->setColor(highlightColor);
	exitLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelHover->enableGlow(glowColor);

	this->storyModeButton = ClickableTextNode::create(
		storyModeLabel,
		storyModeLabelHover,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->minigamesButton = ClickableTextNode::create(
		minigamesLabel,
		minigamesLabelHover,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->optionsButton = ClickableTextNode::create(
		optionsLabel,
		optionsLabelHover,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->exitButton = ClickableTextNode::create(
		exitLabel,
		exitLabelHover,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->ether = Sprite::create(UIResources::Menus_Backgrounds_Ether);
	this->etherParticles = ParticleGalaxy::create();

	this->storyModeButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->minigamesButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->optionsButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->exitButton->setClickSound(SoundResources::Menus_Simple_Button);

	this->addChild(this->background);
	this->addChild(this->ether);
	this->addChild(this->etherParticles);
	this->addChild(this->titleBar);
	this->addChild(this->title);
	this->addChild(this->storyModeButton);
	this->addChild(this->minigamesButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(this->music);
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::onEnter()
{
	super::onEnter();

	this->music->play(true);

	this->initializePositions();
	this->etherParticles->start();
	GameUtils::accelerateParticles(this->etherParticles, 5.0f);
	
	// Fade in slower when the game first boots. Once the user is in the game and navigating menus, this gets annoying if it is too slow.
	static bool firstRun = true;
	const float delay = firstRun ? 0.5f : 0.15f;
	const float duration = firstRun ? 0.75f : 0.25f;

	firstRun = false;

	if (Steam::isSquallyItchBuild())
	{
		this->storyModeButton->disableInteraction();
	}

	GameUtils::fadeInObject(this->ether, delay, duration);
	GameUtils::fadeInObject(this->etherParticles, delay, duration);
	GameUtils::fadeInObject(this->titleBar, delay, duration);
	GameUtils::fadeInObject(this->title, delay, duration);
	GameUtils::fadeInObject(this->storyModeButton, delay, duration);
	GameUtils::fadeInObject(this->minigamesButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

	this->scheduleUpdate();
}

void TitleScreen::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->ether->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));

	this->titleBar->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f));
	this->title->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height - this->title->getContentSize().height / 2));
	this->storyModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f + 288.0f));
	this->minigamesButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f + 144.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f - 0.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f - 256.0f));
}

void TitleScreen::initializeListeners()
{
	super::initializeListeners();

	TitleScreen::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateTitle, [](EventCustom* args)
	{
		GlobalDirector::loadScene(TitleScreen::instance);
	}));

	this->storyModeButton->setMouseClickCallback(CC_CALLBACK_0(TitleScreen::onStoryModeClick, this));
	this->minigamesButton->setMouseClickCallback(CC_CALLBACK_0(TitleScreen::onMinigamesClick, this));
	this->optionsButton->setMouseClickCallback(CC_CALLBACK_0(TitleScreen::onOptionsClick, this));
	this->exitButton->setMouseClickCallback(CC_CALLBACK_0(TitleScreen::onExitClick, this));
}

void TitleScreen::onStoryModeClick()
{
	NavigationEvents::navigateSaveSelect();
}

void TitleScreen::onMinigamesClick()
{
	NavigationEvents::navigateMinigames();
}

void TitleScreen::onOptionsClick()
{
	NavigationEvents::navigateOptions();
}

void TitleScreen::onExitClick()
{
	Director::getInstance()->end();
}
