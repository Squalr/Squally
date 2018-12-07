#include "ConfirmationMenu.h"

ConfirmationMenu* ConfirmationMenu::create()
{
	ConfirmationMenu* instance = new ConfirmationMenu();

	instance->autorelease();

	return instance;
}

ConfirmationMenu::ConfirmationMenu()
{
	this->onConfirmCallback = nullptr;
	this->onCancelCallback = nullptr;

	this->pauseWindow = Sprite::create(UIResources::Menus_ConfirmMenu_ConfirmMenuWindow);
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->cancelButton = MenuSprite::create(UIResources::Menus_Buttons_CancelButton, UIResources::Menus_Buttons_CancelButtonHover);
	this->confirmButton = MenuSprite::create(UIResources::Menus_Buttons_AcceptButton, UIResources::Menus_Buttons_AcceptButtonHover);
	this->confirmationLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->addChild(this->pauseWindow);
	this->addChild(this->closeButton);
	this->addChild(this->cancelButton);
	this->addChild(this->confirmButton);
	this->addChild(this->confirmationLabel);
	this->addChild(Mouse::create());
}

ConfirmationMenu::~ConfirmationMenu()
{
}

void ConfirmationMenu::initialize(std::string confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	this->onConfirmCallback = confirmCallback;
	this->onCancelCallback = cancelCallback;

	this->confirmationLabel->setString(confirmationMessage);
}

void ConfirmationMenu::onEnter()
{
	SmartNode::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ConfirmationMenu::initializePositions()
{
	SmartNode::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->pauseWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 136.0f, visibleSize.height / 2 + 124.0f));
	this->confirmationLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 32.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2 - 96.0f, visibleSize.height / 2 - 64.0f));
	this->confirmButton->setPosition(Vec2(visibleSize.width / 2 + 96.0f, visibleSize.height / 2 - 64.0f));
}

void ConfirmationMenu::initializeListeners()
{
	SmartNode::initializeListeners();

	this->cancelButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onCancelClick, this));
	this->confirmButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onConfirmClick, this));
	this->closeButton->setClickCallback(CC_CALLBACK_1(ConfirmationMenu::onCloseClick, this));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(ConfirmationMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void ConfirmationMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			if (this->onCancelCallback != nullptr)
			{
				this->onCancelCallback();
			}

			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}

void ConfirmationMenu::onCloseClick(MenuSprite* menuSprite)
{
	if (this->onCancelCallback != nullptr)
	{
		this->onCancelCallback();
	}
}

void ConfirmationMenu::onCancelClick(MenuSprite* menuSprite)
{
	if (this->onCancelCallback != nullptr)
	{
		this->onCancelCallback();
	}
}

void ConfirmationMenu::onConfirmClick(MenuSprite* menuSprite)
{
	if (this->onConfirmCallback != nullptr)
	{
		this->onConfirmCallback();
	}
}
