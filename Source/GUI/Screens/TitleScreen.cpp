#include "TitleScreen.h"
#include "Resources.h"

function<void()> theGameStartCallback;

TitleScreen::TitleScreen(function<void()> gameStartCallback)
{
	theGameStartCallback = gameStartCallback;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* titleLabel = Label::createWithTTF("Squalr Tutorial", Resources::Fonts_Marker_Felt, 24);
	Label* startLabel = Label::createWithTTF("Press Enter to Start", Resources::Fonts_Marker_Felt, 16);

	titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - titleLabel->getContentSize().height));
	startLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - startLabel->getContentSize().height / 2));

	this->addChild(titleLabel);
	this->addChild(startLabel);

	this->InitializeListeners();
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TitleScreen::OnKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void TitleScreen::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		theGameStartCallback();
		break;
	}
}
