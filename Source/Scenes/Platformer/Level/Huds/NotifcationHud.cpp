#include "NotificationHud.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/NotificationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

const int NotificationHud::SlotCount = 12;
const float NotificationHud::FadeInDuration = 0.35f;
const float NotificationHud::SustainDuration = 4.0f;
const float NotificationHud::FadeOutDuration = 0.5f;
const float NotificationHud::Cooldown = NotificationHud::FadeInDuration + NotificationHud::SustainDuration + NotificationHud::FadeOutDuration;

using namespace cocos2d;

NotificationHud* NotificationHud::create()
{
	NotificationHud* instance = new NotificationHud();

	instance->autorelease();

	return instance;
}

NotificationHud::NotificationHud()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->previousFocus = nullptr;
	this->contentNode = Node::create();
	this->backdrop = LayerColor::create(Color4B(0, 0, 0, 192), visibleSize.width, visibleSize.height);
	this->menuBack = Sprite::create(UIResources::Menus_ConfirmMenu_ConfirmMenu);
	this->title = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, Strings::Common_Empty::create());
	this->description = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create(), Size(560.0f, 0.0f));
	this->confirmationMenu = ConfirmationMenu::create();
	this->notificationSound = Sound::create();
	this->takeoverNode = Node::create();
	this->notificationsNode = Node::create();
	this->slotCooldowns = std::vector<float>();

	LocalizedLabel* okLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Okay::create());
	LocalizedLabel* okLabelSelected = okLabel->clone();

	okLabel->enableOutline(Color4B::BLACK, 2);
	okLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->okButton = ClickableTextNode::create(okLabel, okLabelSelected, UIResources::Menus_Buttons_WoodButton, UIResources::Menus_Buttons_WoodButtonSelected);

	this->title->enableOutline(Color4B::BLACK, 2);
	this->description->enableOutline(Color4B::BLACK, 2);

	for (int index = 0; index < NotificationHud::SlotCount; index++)
	{
		this->slotCooldowns.push_back(NotificationHud::Cooldown);
	}

	this->takeoverNode->addChild(this->backdrop);
	this->takeoverNode->addChild(this->menuBack);
	this->takeoverNode->addChild(this->title);
	this->takeoverNode->addChild(this->description);
	this->takeoverNode->addChild(this->okButton);
	this->contentNode->addChild(this->takeoverNode);
	this->contentNode->addChild(this->notificationsNode);
	this->contentNode->addChild(this->confirmationMenu);
	this->contentNode->addChild(this->notificationSound);
	this->addChild(this->contentNode);
}

NotificationHud::~NotificationHud()
{
}

void NotificationHud::onEnter()
{
	super::onEnter();

	this->takeoverNode->setVisible(false);
	this->scheduleUpdate();
}

void NotificationHud::initializePositions()
{
	super::initializePositions();

	static const Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->backdrop->setPosition(Vec2(-visibleSize.width / 2.0f, -visibleSize.height / 2.0f));
	this->menuBack->setPosition(Vec2(0.0f, 0.0f));
	this->okButton->setPosition(Vec2(0.0f, - 192.0f));
	this->title->setPosition(Vec2(0.0f, 204.0f));
	this->description->setPosition(Vec2(0.0f, 32.0f));
	this->takeoverNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void NotificationHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventNotificationTakeover, [=](EventCustom* eventCustom)
	{
		NotificationEvents::NotificationTakeoverArgs* args = static_cast<NotificationEvents::NotificationTakeoverArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->showNotificationTakeover(args->title, args->description, args->soundResource);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventNotification, [=](EventCustom* eventCustom)
	{
		NotificationEvents::NotificationArgs* args = static_cast<NotificationEvents::NotificationArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->pushNotification(args->title, args->description, args->iconResource, args->soundResource, args->keepOpen);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventConfirmation, [=](EventCustom* eventCustom)
	{
		NotificationEvents::ConfirmationArgs* args = static_cast<NotificationEvents::ConfirmationArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->confirmationMenu->showMessage(args->confirmationMessage, args->confirmCallback, args->cancelCallback);
		}
	}));

	this->okButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->closeNotificationMenu();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE, EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this->takeoverNode))
		{
			return;
		}

		args->handle();
		
		this->closeNotificationMenu();
	});
}

void NotificationHud::update(float dt)
{
	super::update(dt);

	for (int index = 0; index < int(this->slotCooldowns.size()); index++)
	{
		this->slotCooldowns[index] += dt;

		if (!this->toProcess.empty())
		{
			if (this->slotCooldowns[index] >= Cooldown)
			{
				Node* notification = this->toProcess.front();
				this->toProcess.pop();

				static const Size visibleSize = Director::getInstance()->getVisibleSize();
				static const Vec2 LeftPositionBase = Vec2(256.0f, 128.0f);
				static const Vec2 RightPositionBase = Vec2(visibleSize.width - 256.0f, 128.0f);
				int halfCount = int(this->slotCooldowns.size() / 2);
				Vec2 basePosition = index < halfCount ? RightPositionBase : LeftPositionBase;

				notification->setPosition(basePosition + Vec2(0.0f, float(index % halfCount) * 160.0f));
				
				if (bool(notification->getTag()))
				{
					// Slight hack. If the keep open flag is set on the object, just never hide the notification.
					// This is used in situations like combat, where we do not expect to exhaust the full # of possible notifications shown,
					// So keeping them always visible is fine. This HUD will get disposed when they leave combat anyhow.
					notification->runAction(Sequence::create(
						FadeTo::create(FadeInDuration, 255),
						DelayTime::create(SustainDuration),
						nullptr
					));
				}
				else
				{
					notification->runAction(Sequence::create(
						FadeTo::create(FadeInDuration, 255),
						DelayTime::create(SustainDuration),
						FadeTo::create(FadeOutDuration, 0),
						nullptr
					));
				}

				this->slotCooldowns[index] = 0.0f;
			}
		}
	}
}

void NotificationHud::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->contentNode->setVisible(false);
}

void NotificationHud::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->contentNode->setVisible(true);
}

void NotificationHud::showNotificationTakeover(LocalizedString* title, LocalizedString* description, std::string soundResource)
{
	this->title->setLocalizedString(title);
	this->description->setLocalizedString(description);
	this->takeoverNode->setVisible(true);
	this->notificationSound->setSoundResource(soundResource);
	
	this->previousFocus = GameUtils::getFocusedNode();
	GameUtils::focus(this);

	if (!this->notificationSound->isPlaying())
	{
		this->notificationSound->play();
	}
}

void NotificationHud::pushNotification(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource, bool keepOpen)
{
	Node* notification = Node::create();
	Sprite* itemFrame = Sprite::create(UIResources::Menus_NotificationMenu_NotificationFrame);
	Sprite* notificationIcon = Sprite::create(iconResource);
	LocalizedLabel* titleLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, title);
	LocalizedLabel* descriptionLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, description, Size(192.0f, 0.0f));

	this->notificationSound->setSoundResource(soundResource);

	titleLabel->enableOutline(Color4B::BLACK, 2);
	descriptionLabel->enableOutline(Color4B::BLACK, 2);

	notificationIcon->setPosition(Vec2(-144.0f, 0.0f));
	descriptionLabel->setPosition(Vec2(32.0f, 0.0f));
	titleLabel->setPosition(Vec2(0.0f, 72.0f));

	notification->setOpacity(0);

	notification->addChild(itemFrame);
	notification->addChild(notificationIcon);
	notification->addChild(descriptionLabel);
	notification->addChild(titleLabel);
	this->notificationsNode->addChild(notification);

	if (!this->notificationSound->isPlaying())
	{
		this->notificationSound->play();
	}

	notification->setTag(int(keepOpen));

	this->toProcess.push(notification);
}

void NotificationHud::closeNotificationMenu()
{
	this->takeoverNode->setVisible(false);

	if (this->previousFocus != nullptr)
	{
		GameUtils::focus(this->previousFocus);
	}
}
