#include "CollectablesMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Menus/Collectables/Collectables.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

CollectablesMenu* CollectablesMenu::create()
{
	CollectablesMenu* instance = new CollectablesMenu();

	instance->autorelease();

	return instance;
}

CollectablesMenu::CollectablesMenu()
{
	this->collectablesWindow = Sprite::create(UIResources::Menus_Generic_LargeMenu);
	this->closeButton = ClickableNode::create(UIResources::Menus_IngameMenu_CloseButton, UIResources::Menus_IngameMenu_CloseButtonSelected);
	this->collectablesLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H1, Strings::Menus_Collectables_Collectables::create());
	this->returnClickCallback = nullptr;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = returnLabel->clone();

	returnLabel->enableOutline(Color4B::BLACK, 2);
	returnLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabel->enableGlow(Color4B::BLACK);
	returnLabelHover->enableOutline(Color4B::BLACK, 2);
	returnLabelHover->setTextColor(Color4B::YELLOW);
	returnLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	returnLabelHover->enableGlow(Color4B::ORANGE);

	this->returnButton = ClickableTextNode::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected);

	this->collectablesLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	this->collectablesLabel->enableGlow(Color4B::BLACK);

	this->addChild(this->collectablesWindow);
	this->addChild(this->collectablesLabel);
	this->addChild(this->closeButton);
	this->addChild(this->returnButton);
}

CollectablesMenu::~CollectablesMenu()
{
}

void CollectablesMenu::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->collectablesWindow, delay, duration);
	GameUtils::fadeInObject(this->collectablesLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);
}

void CollectablesMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->collectablesWindow->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->collectablesLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 380.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 580.0f, visibleSize.height / 2.0f + 368.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 472.0f));
}

void CollectablesMenu::initializeListeners()
{
	super::initializeListeners();

	this->returnButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});

	this->closeButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
	this->closeButton->setClickSound(SoundResources::ClickBack1);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handled = true;

		if (this->returnClickCallback != nullptr)
		{
			this->returnClickCallback();
		}
	});
}

void CollectablesMenu::setReturnClickCallback(std::function<void()> returnClickCallback)
{
	this->returnClickCallback = returnClickCallback;
}
