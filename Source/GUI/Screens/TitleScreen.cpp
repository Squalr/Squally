#include "TitleScreen.h"
#include "Resources.h"

function<void()> theGameStartCallback;

TitleScreen::TitleScreen(function<void()> gameStartCallback)
{
	theGameStartCallback = gameStartCallback;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Label* label = Label::createWithTTF("Squalr Tutorial", Resources::Fonts_Marker_Felt, 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	this->InitializeListeners();
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TitleScreen::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void TitleScreen::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		theGameStartCallback();
		break;
	}
}
