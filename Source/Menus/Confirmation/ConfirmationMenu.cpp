#include "ConfirmationMenu.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NotificationEvents.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ConfirmationMenu* ConfirmationMenu::create()
{
	ConfirmationMenu* instance = new ConfirmationMenu();

	instance->autorelease();

	return instance;
}

ConfirmationMenu::ConfirmationMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 196), visibleSize.width, visibleSize.height);

	this->onConfirmCallback = nullptr;
	this->onCancelCallback = nullptr;

	this->confirmationLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create(), Size(560.0f, 0.0f));
	this->confirmWindow = Sprite::create(UIResources::Menus_ConfirmMenu_ConfirmMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->closeButton->setClickSound(SoundResources::Menus_ClickBack1);
	
	LocalizedLabel*	cancelLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Cancel::create());
	LocalizedLabel*	cancelLabelHover = cancelLabel->clone();

	cancelLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabel->enableGlow(Color4B::BLACK);

	cancelLabelHover->setColor(Color3B::YELLOW);
	cancelLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	cancelLabelHover->enableGlow(Color4B::ORANGE);

	this->cancelButton = ClickableTextNode::create(
		cancelLabel,
		cancelLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);
	this->cancelButton->setClickSound(SoundResources::Menus_ClickBack1);

	LocalizedLabel*	confirmLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Accept::create());
	LocalizedLabel*	confirmLabelHover = confirmLabel->clone();

	confirmLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	confirmLabel->enableGlow(Color4B::BLACK);

	confirmLabelHover->setColor(Color3B::YELLOW);
	confirmLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	confirmLabelHover->enableGlow(Color4B::ORANGE);

	this->confirmButton = ClickableTextNode::create(
		confirmLabel,
		confirmLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->confirmationLabel->enableOutline(Color4B::BLACK, 2);
	this->confirmationLabel->setHorizontalAlignment(TextHAlignment::CENTER);

	this->setVisible(false);

	this->addChild(this->backdrop);
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

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->close();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE, InputEvents::KeyCode::KEY_ENTER }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}

		args->handle();

		this->confirm();
	});
}

void ConfirmationMenu::disableBackdrop()
{
	this->backdrop->setVisible(false);
}

void ConfirmationMenu::showMessage(LocalizedString* confirmationMessage, std::function<bool()> confirmCallback, std::function<bool()> cancelCallback)
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
		if (this->onConfirmCallback())
		{
			return;
		}
	}

	NotificationEvents::TriggerConfirmationEnd();
	
	this->setVisible(false);
}

void ConfirmationMenu::close()
{
	if (this->onCancelCallback != nullptr)
	{
		if (this->onCancelCallback())
		{
			return;
		}
	}
	
	NotificationEvents::TriggerConfirmationEnd();

	this->setVisible(false);
}
