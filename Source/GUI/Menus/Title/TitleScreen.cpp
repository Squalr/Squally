#include "TitleScreen.h"

TitleScreen * TitleScreen::create()
{
	TitleScreen* titleScreen = new TitleScreen();

	titleScreen->autorelease();

	return titleScreen;
}

TitleScreen::TitleScreen()
{
	this->titleBar = Sprite::create(Resources::Menus_TitleScreen_TitleBar);
	this->title = Sprite::create(Resources::Menus_TitleScreen_Title);
	this->background = TitleScreenBackground::create();
	this->storyModeButton = MenuSprite::create(Sprite::create(Resources::Menus_TitleScreen_StoryModeButton), Resources::Menus_TitleScreen_StoryModeButtonHover, Resources::Menus_TitleScreen_StoryModeButtonClick);
	this->optionsButton = MenuSprite::create(Sprite::create(Resources::Menus_TitleScreen_OptionsButton), Resources::Menus_TitleScreen_OptionsButtonHover, Resources::Menus_TitleScreen_OptionsButtonClick);
	this->exitButton = MenuSprite::create(Sprite::create(Resources::Menus_TitleScreen_ExitButton), Resources::Menus_TitleScreen_ExitButtonHover, Resources::Menus_TitleScreen_ExitButtonClick);

	this->ether = MenuSprite::create(Sprite::create(Resources::Menus_Backgrounds_Ether), Resources::Menus_Backgrounds_EtherSelected, Resources::Menus_Backgrounds_EtherSelected);
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
	NavigationEvents::navigate(NavigationEvents::GameScreen::StoryMap);
}

void TitleScreen::onOptionsClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigate(NavigationEvents::GameScreen::Options);
}

void TitleScreen::onExitClick(MenuSprite* menuSprite)
{
	Director::getInstance()->end();
}
