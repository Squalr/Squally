#include "TitleScreen.h"

const std::string TitleScreen::StringKeyStoryMode = "Menu_Story_Mode";
const std::string TitleScreen::StringKeyMinigames = "Menu_Minigames";
const std::string TitleScreen::StringKeyOptions = "Menu_Options";
const std::string TitleScreen::StringKeyExit = "Menu_Exit";

const float TitleScreen::titleFontSize = 64.0f;
const float TitleScreen::menuFontSize = 48.0f;
const float TitleScreen::menuOffset = 128.0f;
const float TitleScreen::spacing = -96.0f;

TitleScreen * TitleScreen::create()
{
	TitleScreen* instance = new TitleScreen();

	instance->autorelease();

	return instance;
}

TitleScreen::TitleScreen()
{
	this->titleBar = Sprite::create(Resources::Menus_TitleScreen_TitleBar);
	this->title = Sprite::create(Resources::Menus_TitleScreen_Title);
	this->background = TitleScreenBackground::create();
	
	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	Label* storyModeLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyStoryMode), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* storyModeLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyStoryMode), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* arcadeModeLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyMinigames), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* arcadeModeLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyMinigames), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* optionsLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyOptions), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* optionsLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyOptions), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* exitLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyExit), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* exitLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyExit), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	storyModeLabel->setColor(textColor);
	storyModeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabel->enableGlow(shadowColor);
	arcadeModeLabel->setColor(textColor);
	arcadeModeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	arcadeModeLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);

	storyModeLabelHover->setColor(highlightColor);
	storyModeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabelHover->enableGlow(glowColor);
	arcadeModeLabelHover->setColor(highlightColor);
	arcadeModeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	arcadeModeLabelHover->enableGlow(glowColor);
	optionsLabelHover->setColor(highlightColor);
	optionsLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelHover->enableGlow(glowColor);
	exitLabelHover->setColor(highlightColor);
	exitLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelHover->enableGlow(glowColor);

	this->storyModeButton = TextMenuSprite::create(
		storyModeLabel,
		storyModeLabelHover,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover);

	this->arcadeModeButton = TextMenuSprite::create(
		arcadeModeLabel,
		arcadeModeLabelHover,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover);

	this->optionsButton = TextMenuSprite::create(
		optionsLabel,
		optionsLabelHover,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover);

	this->exitButton = TextMenuSprite::create(
		exitLabel,
		exitLabelHover,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover);

	this->ether = Sprite::create(Resources::Menus_Backgrounds_Ether);
	this->etherParticles = ParticleGalaxy::create();

	this->addChild(this->background);
	this->addChild(this->ether);
	this->addChild(this->etherParticles);
	this->addChild(this->titleBar);
	this->addChild(this->title);
	this->addChild(this->storyModeButton);
	this->addChild(this->arcadeModeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);
	this->addChild(Mouse::create());
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::onEnter()
{
	FadeScene::onEnter();

	SoundManager::playMusicResource(Resources::Music_WeWillGetThereTogether);

	this->initializePositions();
	this->etherParticles->start();
	GameUtils::accelerateParticles(this->etherParticles, 5.0f);

	this->storyModeButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onStoryModeClick, this));
	this->storyModeButton->setClickSound(Resources::Sounds_Menus_Simple_Button);
	this->arcadeModeButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onArcadeModeClick, this));
	this->arcadeModeButton->setClickSound(Resources::Sounds_Menus_Simple_Button);
	this->optionsButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onOptionsClick, this));
	this->optionsButton->setClickSound(Resources::Sounds_Menus_Simple_Button);
	this->exitButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onExitClick, this));
	this->exitButton->setClickSound(Resources::Sounds_Menus_Simple_Button);
	


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
	GameUtils::fadeInObject(this->arcadeModeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

	this->scheduleUpdate();

	// TEMPORARY FOR DEMO:
	this->storyModeButton->disableInteraction(0);
	GameUtils::fadeInObject(this->storyModeButton, delay, duration, 128);
}

void TitleScreen::initializePositions()
{
	FadeScene::initializePositions();
	
	this->background->initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->ether->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - this->ether->getContentSize().height + 372.0f));

	this->titleBar->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f));
	this->title->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height - this->title->getContentSize().height / 2));
	this->storyModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f + 288.0f));
	this->arcadeModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f + 144.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f - 0.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2.0f - visibleSize.width / 3.0f, origin.y + visibleSize.height / 2.0f - 256.0f));
}

void TitleScreen::onStoryModeClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::SaveSelect);
}

void TitleScreen::onArcadeModeClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Minigames);
}

void TitleScreen::onOptionsClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Options);
}

void TitleScreen::onExitClick(MenuSprite* menuSprite)
{
	Director::getInstance()->end();
}
