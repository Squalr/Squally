#include "ConfirmationMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

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

	this->confirmationLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create(), Size(560.0f, 0.0f));
	this->confirmWindow = Sprite::create(UIResources::Menus_ConfirmMenu_ConfirmMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->cancelButton = ClickableNode::create(UIResources::Menus_Buttons_CancelButton, UIResources::Menus_Buttons_CancelButtonHover);
	this->confirmButton = ClickableNode::create(UIResources::Menus_Buttons_AcceptButton, UIResources::Menus_Buttons_AcceptButtonHover);
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->confirmationLabel->enableOutline(Color4B::BLACK, 2);

	this->setVisible(false);

	this->addChild(this->confirmWindow);
	this->addChild(this->confirmationLabel);
	this->addChild(this->closeButton);
	this->addChild(this->cancelButton);
	this->addChild(this->confirmButton);
}

ConfirmationMenu::~ConfirmationMenu()
{
}

void ConfirmationMenu::onEnter()
{
	super::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void ConfirmationMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->confirmWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->confirmationLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2 + 32.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 224.0f, visibleSize.height / 2 + 212.0f));
	this->cancelButton->setPosition(Vec2(visibleSize.width / 2 - 160.0f, visibleSize.height / 2 - 192.0f));
	this->confirmButton->setPosition(Vec2(visibleSize.width / 2 + 160.0f, visibleSize.height / 2 - 192.0f));
}

void ConfirmationMenu::initializeListeners()
{
	super::initializeListeners();

	this->cancelButton->setMouseClickCallback(CC_CALLBACK_0(ConfirmationMenu::close, this));
	this->confirmButton->setMouseClickCallback(CC_CALLBACK_0(ConfirmationMenu::confirm, this));
	this->closeButton->setMouseClickCallback(CC_CALLBACK_0(ConfirmationMenu::close, this));

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isFocused(this))
		{
			return;
		}
		
		args->handled = true;

		this->close();
	});
}

void ConfirmationMenu::showMessage(LocalizedString* confirmationMessage, std::function<void()> confirmCallback, std::function<void()> cancelCallback)
{
	this->confirmationLabel->setLocalizedString(confirmationMessage);
	this->onConfirmCallback = confirmCallback;
	this->onCancelCallback = cancelCallback;

	this->setVisible(true);
}

void ConfirmationMenu::confirm()
{
	if (this->onConfirmCallback != nullptr)
	{
		this->onConfirmCallback();
	}
	
	this->setVisible(false);
}

void ConfirmationMenu::close()
{
	if (this->onCancelCallback != nullptr)
	{
		this->onCancelCallback();
	}

	this->setVisible(false);
}
