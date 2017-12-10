#include "TitleScreen.h"

const float titleFontSize = 24.0f;
const float menuFontSize = 16.0f;
const float menuOffset = 64.0f;
const float spacing = -40.0f;

TitleScreen::TitleScreen(function<void()> gameStartCallback)
{
	this->theGameStartCallback = gameStartCallback;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::GUI_TitleScreen_TitleScreen);
	this->titleLabel = new MenuLabel("Squally", Resources::Fonts_Marker_Felt, titleFontSize);
	this->storyModeLabel = new MenuLabel("Story Mode", Resources::Fonts_Marker_Felt, menuFontSize);
	this->tutorialModeLabel = new MenuLabel("Tutorial Mode", Resources::Fonts_Marker_Felt, menuFontSize);
	this->optionsLabel = new MenuLabel("Options", Resources::Fonts_Marker_Felt, menuFontSize);
	this->exitLabel = new MenuLabel("Exit", Resources::Fonts_Marker_Felt, menuFontSize);

	this->mouse = new Mouse();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
	this->storyModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->storyModeLabel->getContentSize().height / 2 + menuOffset + spacing * 0));
	this->tutorialModeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 1));
	this->optionsLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 2));
	this->exitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->tutorialModeLabel->getContentSize().height / 2 + menuOffset + spacing * 3));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->storyModeLabel);
	this->addChild(this->tutorialModeLabel);
	this->addChild(this->optionsLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

	this->InitializeListeners();
}

TitleScreen::~TitleScreen()
{
	delete(this->mouse);
}

void TitleScreen::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(TitleScreen::OnKeyPressed, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(TitleScreen::OnMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void TitleScreen::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		theGameStartCallback();
		break;
	}
}

void TitleScreen::OnMouseMove(EventMouse* event)
{

}
