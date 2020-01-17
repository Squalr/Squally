#include "TitleScreen.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCParticleExamples.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Music.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Options/OptionsScene.h"
#include "Menus/SaveSelect/SaveSelectMenu.h"
#include "Menus/TutorialSelect/TutorialSelectMenu.h"
#include "Scenes/Title/TitleScreenBackground.h"
#include "Scenes/Developer/DeveloperScene.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TitleScreen* TitleScreen::instance = nullptr;

TitleScreen* TitleScreen::getInstance()
{
	if (TitleScreen::instance == nullptr)
	{
		TitleScreen::instance = new TitleScreen();

		TitleScreen::instance->autorelease();
		TitleScreen::instance->initializeListeners();

		GlobalDirector::registerGlobalScene(TitleScreen::getInstance());
	}

	return TitleScreen::instance;
}

TitleScreen::TitleScreen()
{
	this->titleBar = Sprite::create(UIResources::Menus_TitleScreen_TitleBar);
	this->title = Sprite::create(UIResources::Menus_TitleScreen_Title);
	this->background = TitleScreenBackground::create();
	this->music = Music::createAndAddGlobally(MusicResources::WeWillGetThereTogether, this);
	
	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	LocalizedLabel*	storyModeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_StoryMode::create());
	LocalizedLabel*	storyModeLabelSelected = storyModeLabel->clone();

	LocalizedLabel*	tutorialsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_HackingTutorials::create());
	LocalizedLabel*	tutorialsLabelSelected = tutorialsLabel->clone();

	LocalizedLabel*	optionsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Options_Options::create());
	LocalizedLabel*	optionsLabelSelected = optionsLabel->clone();

	LocalizedLabel*	exitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Exit::create());
	LocalizedLabel*	exitLabelSelected = exitLabel->clone();

	LocalizedLabel*	debugLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Developer_DeveloperMenu::create());
	LocalizedLabel*	debugLabelSelected = debugLabel->clone();

	storyModeLabel->setColor(textColor);
	storyModeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabel->enableGlow(shadowColor);
	tutorialsLabel->setColor(textColor);
	tutorialsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	tutorialsLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);
	debugLabel->setColor(textColor);
	debugLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	debugLabel->enableGlow(shadowColor);

	storyModeLabelSelected->setColor(highlightColor);
	storyModeLabelSelected->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabelSelected->enableGlow(glowColor);
	tutorialsLabelSelected->setColor(highlightColor);
	tutorialsLabelSelected->enableShadow(shadowColor, shadowSize, shadowBlur);
	tutorialsLabelSelected->enableGlow(glowColor);
	optionsLabelSelected->setColor(highlightColor);
	optionsLabelSelected->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelSelected->enableGlow(glowColor);
	exitLabelSelected->setColor(highlightColor);
	exitLabelSelected->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelSelected->enableGlow(glowColor);
	debugLabelSelected->setColor(highlightColor);
	debugLabelSelected->enableShadow(shadowColor, shadowSize, shadowBlur);
	debugLabelSelected->enableGlow(glowColor);

	this->storyModeButton = ClickableTextNode::create(
		storyModeLabel,
		storyModeLabelSelected,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->tutorialsButton = ClickableTextNode::create(
		tutorialsLabel,
		tutorialsLabelSelected,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->optionsButton = ClickableTextNode::create(
		optionsLabel,
		optionsLabelSelected,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->exitButton = ClickableTextNode::create(
		exitLabel,
		exitLabelSelected,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->debugButton = ClickableTextNode::create(
		debugLabel,
		debugLabelSelected,
		UIResources::Menus_TitleScreen_TitleButton,
		UIResources::Menus_TitleScreen_TitleButtonHover);

	this->ether = Sprite::create(UIResources::Menus_Backgrounds_Ether);
	this->etherParticles = ParticleGalaxy::create();

	this->storyModeButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->tutorialsButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->optionsButton->setClickSound(SoundResources::Menus_Simple_Button);
	this->exitButton->setClickSound(SoundResources::Menus_Simple_Button);

	if (!DeveloperModeController::IsDeveloperBuild)
	{
		this->debugButton->setVisible(false);
	}

	this->addChild(this->background);
	this->addChild(this->ether);
	this->addChild(this->etherParticles);
	this->addChild(this->titleBar);
	this->addChild(this->title);
	this->addChild(this->storyModeButton);
	this->addChild(this->tutorialsButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(this->debugButton);
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::onEnter()
{
	super::onEnter();

	MusicPlayer::play(this->music, true);

	this->etherParticles->start();
	GameUtils::accelerateParticles(this->etherParticles, 5.0f);
	
	// Fade in slower when the game first boots. Once the user is in the game and navigating menus, this gets annoying if it is too slow.
	static bool firstRun = true;
	const float delay = firstRun ? 0.5f : 0.15f;
	const float duration = firstRun ? 0.75f : 0.25f;

	firstRun = false;

	GameUtils::fadeInObject(this->ether, delay, duration);
	GameUtils::fadeInObject(this->etherParticles, delay, duration);
	GameUtils::fadeInObject(this->titleBar, delay, duration);
	GameUtils::fadeInObject(this->title, delay, duration);
	GameUtils::fadeInObject(this->storyModeButton, delay, duration);
	GameUtils::fadeInObject(this->tutorialsButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);
	GameUtils::fadeInObject(this->debugButton, delay, duration);

	this->scheduleUpdate();
}

void TitleScreen::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->ether->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));

	this->titleBar->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f));
	this->title->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height - this->title->getContentSize().height / 2));
	this->storyModeButton->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f + 288.0f));
	this->tutorialsButton->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f + 288.0f - 144.0f));
	this->optionsButton->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f - 144.0f));
	this->exitButton->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f - 288.0f));
	this->debugButton->setPosition(Vec2(visibleSize.width / 2.0f - visibleSize.width / 3.0f, visibleSize.height / 2.0f - 288.0f - 144.0f));
}

void TitleScreen::initializeListeners()
{
	super::initializeListeners();

	this->storyModeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args) { NavigationEvents::LoadScene(SaveSelectMenu::getInstance()); });
	this->tutorialsButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args) { NavigationEvents::LoadScene(TutorialSelectMenu::getInstance()); });
	this->optionsButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args) { NavigationEvents::LoadScene(OptionsScene::getInstance()); });
	this->exitButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args) { Director::getInstance()->end(); });
	this->debugButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args) { NavigationEvents::LoadScene(DeveloperScene::getInstance()); });
}
