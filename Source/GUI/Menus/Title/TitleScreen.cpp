#include "TitleScreen.h"

TitleScreen * TitleScreen::create()
{
	TitleScreen* titleScreen = new TitleScreen();

	titleScreen->autorelease();

	return titleScreen;
}

TitleScreen::TitleScreen()
{
	SoundManager::GetInstance()->PlayMusicResource(Resources::Music_Will_we_get_there_Together);

	this->titleBar = Sprite::create(Resources::Menus_TitleScreen_TitleBar);
	this->title = Sprite::create(Resources::Menus_TitleScreen_Title);
	this->background = TitleScreenBackground::create();
	this->storyModeButton = MenuSprite::create(Resources::Menus_TitleScreen_StoryModeButton, Resources::Menus_TitleScreen_StoryModeButtonHover, Resources::Menus_TitleScreen_StoryModeButtonClick);
	this->optionsButton = MenuSprite::create(Resources::Menus_TitleScreen_OptionsButton, Resources::Menus_TitleScreen_OptionsButtonHover, Resources::Menus_TitleScreen_OptionsButtonClick);
	this->exitButton = MenuSprite::create(Resources::Menus_TitleScreen_ExitButton, Resources::Menus_TitleScreen_ExitButtonHover, Resources::Menus_TitleScreen_ExitButtonClick);

	this->background->SetMatrixClickCallback(CC_CALLBACK_1(TitleScreen::OnMatrixClick, this));
	this->storyModeButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnStoryModeClick, this));
	this->optionsButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnOptionsClick, this));
	this->exitButton->SetClickCallback(CC_CALLBACK_1(TitleScreen::OnExitClick, this));

	this->addChild(this->background);
	this->addChild(this->titleBar);
	this->addChild(this->title);
	this->addChild(this->storyModeButton);
	this->addChild(this->optionsButton);
	this->addChild(this->exitButton);

	this->scheduleUpdate();
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::onEnter()
{
	Scene::onEnter();

	this->background->InitializePositions();
	this->InitializePositions();

	this->addChild(Mouse::claimInstance());
}

void TitleScreen::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->titleBar->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2));
	this->title->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height - this->title->getContentSize().height / 2));
	this->storyModeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 192.0f));
	this->optionsButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 + 64.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - visibleSize.width / 3, origin.y + visibleSize.height / 2 - 128.0f));
}

void TitleScreen::OnMatrixClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(TutorialScreen::create());
}

void TitleScreen::OnStoryModeClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(StoryMap::create());
}

void TitleScreen::OnOptionsClick(MenuSprite* menuSprite)
{
	Director::getInstance()->pushScene(OptionsMenu::create());
}

void TitleScreen::OnExitClick(MenuSprite* menuSprite)
{
	Director::getInstance()->end();
}
