#include "TitleScreen.h"

const std::string TitleScreen::StringKeyStoryMode = "Menu_Story_Mode";
const std::string TitleScreen::StringKeyOptions = "Menu_Options";
const std::string TitleScreen::StringKeyExit = "Menu_Exit";

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
	
	Size shadowSize = Size(-4.0f, -4.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	Label* storyModeLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyStoryMode), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* storyModeLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyStoryMode), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* storyModeLabelClicked = Label::create(Localization::resolveString(TitleScreen::StringKeyStoryMode), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* optionsLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyOptions), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* optionsLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyOptions), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* optionsLabelClicked = Label::create(Localization::resolveString(TitleScreen::StringKeyOptions), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	Label* exitLabel = Label::create(Localization::resolveString(TitleScreen::StringKeyExit), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* exitLabelHover = Label::create(Localization::resolveString(TitleScreen::StringKeyExit), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* exitLabelClicked = Label::create(Localization::resolveString(TitleScreen::StringKeyExit), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	storyModeLabel->setColor(textColor);
	storyModeLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabel->enableGlow(shadowColor);
	optionsLabel->setColor(textColor);
	optionsLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabel->enableGlow(shadowColor);
	exitLabel->setColor(textColor);
	exitLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabel->enableGlow(shadowColor);

	storyModeLabelHover->setColor(highlightColor);
	storyModeLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabelHover->enableGlow(glowColor);
	optionsLabelHover->setColor(highlightColor);
	optionsLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelHover->enableGlow(glowColor);
	exitLabelHover->setColor(highlightColor);
	exitLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelHover->enableGlow(glowColor);

	storyModeLabelClicked->setColor(highlightColor);
	storyModeLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	storyModeLabelClicked->enableGlow(glowColor);
	optionsLabelClicked->setColor(highlightColor);
	optionsLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	optionsLabelClicked->enableGlow(glowColor);
	exitLabelClicked->setColor(highlightColor);
	exitLabelClicked->enableShadow(shadowColor, shadowSize, shadowBlur);
	exitLabelClicked->enableGlow(glowColor);

	this->storyModeButton = TextMenuSprite::create(
		storyModeLabel,
		storyModeLabelHover,
		storyModeLabelClicked,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover,
		Resources::Menus_TitleScreen_TitleButtonClick);

	this->optionsButton = TextMenuSprite::create(
		optionsLabel,
		optionsLabelHover,
		optionsLabelClicked,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover,
		Resources::Menus_TitleScreen_TitleButtonClick);

	this->exitButton = TextMenuSprite::create(
		exitLabel,
		exitLabelHover,
		exitLabelClicked,
		Resources::Menus_TitleScreen_TitleButton,
		Resources::Menus_TitleScreen_TitleButtonHover,
		Resources::Menus_TitleScreen_TitleButtonClick);

	this->ether = MenuSprite::create(Resources::Menus_Backgrounds_Ether, Resources::Menus_Backgrounds_EtherSelected, Resources::Menus_Backgrounds_EtherSelected);
	this->etherParticles = ParticleGalaxy::create();

	this->addChild(this->background);
	this->addChild(this->ether);
	this->addChild(this->etherParticles);
	this->addChild(this->titleBar);
	this->addChild(this->title);
	this->addChild(this->storyModeButton);
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

	this->ether->setClickCallback(CC_CALLBACK_1(TitleScreen::onMatrixClick, this));
	this->storyModeButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onStoryModeClick, this));
	this->optionsButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onOptionsClick, this));
	this->exitButton->setClickCallback(CC_CALLBACK_1(TitleScreen::onExitClick, this));

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameUtils::fadeInObject(this->ether, delay, duration);
	GameUtils::fadeInObject(this->etherParticles, delay, duration);
	GameUtils::fadeInObject(this->titleBar, delay, duration);
	GameUtils::fadeInObject(this->title, delay, duration);
	GameUtils::fadeInObject(this->storyModeButton, delay, duration);
	GameUtils::fadeInObject(this->optionsButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

	this->scheduleUpdate();
}

void TitleScreen::initializePositions()
{
	this->background->initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->ether->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));
	this->etherParticles->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - this->ether->getContentSize().height + 372.0f));

	this->titleBar->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2));
	this->title->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height - this->title->getContentSize().height / 2));
	this->storyModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 192.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 64.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 - 128.0f));
}

void TitleScreen::onMatrixClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Tutorial);
}

void TitleScreen::onStoryModeClick(MenuSprite* menuSprite)
{
	//// NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap);
	NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneIntroSpace);
}

void TitleScreen::onOptionsClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Options);
}

void TitleScreen::onExitClick(MenuSprite* menuSprite)
{
	Director::getInstance()->end();
}
